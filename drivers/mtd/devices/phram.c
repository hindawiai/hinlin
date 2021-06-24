<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) ????		Jochen Schथअuble <psionic@psionic.de>
 * Copyright (c) 2003-2004	Joern Engel <joern@wh.fh-wedel.de>
 *
 * Usage:
 *
 * one commend line parameter per device, each in the क्रमm:
 *   phram=<name>,<start>,<len>[,<erasesize>]
 * <name> may be up to 63 अक्षरacters.
 * <start>, <len>, and <erasesize> can be octal, decimal or hexadecimal.  If followed
 * by "ki", "Mi" or "Gi", the numbers will be पूर्णांकerpreted as kilo, mega or
 * gigabytes. <erasesize> is optional and शेषs to PAGE_SIZE.
 *
 * Example:
 *	phram=swap,64Mi,128Mi phram=test,900Mi,1Mi,64Ki
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <यंत्र/भाग64.h>

काष्ठा phram_mtd_list अणु
	काष्ठा mtd_info mtd;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(phram_list);

अटल पूर्णांक phram_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	u_अक्षर *start = mtd->priv;

	स_रखो(start + instr->addr, 0xff, instr->len);

	वापस 0;
पूर्ण

अटल पूर्णांक phram_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	*virt = mtd->priv + from;
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक phram_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक phram_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	u_अक्षर *start = mtd->priv;

	स_नकल(buf, start + from, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक phram_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	u_अक्षर *start = mtd->priv;

	स_नकल(start + to, buf, len);
	*retlen = len;
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_devices(व्योम)
अणु
	काष्ठा phram_mtd_list *this, *safe;

	list_क्रम_each_entry_safe(this, safe, &phram_list, list) अणु
		mtd_device_unरेजिस्टर(&this->mtd);
		iounmap(this->mtd.priv);
		kमुक्त(this->mtd.name);
		kमुक्त(this);
	पूर्ण
पूर्ण

अटल पूर्णांक रेजिस्टर_device(अक्षर *name, phys_addr_t start, माप_प्रकार len, uपूर्णांक32_t erasesize)
अणु
	काष्ठा phram_mtd_list *new;
	पूर्णांक ret = -ENOMEM;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		जाओ out0;

	ret = -EIO;
	new->mtd.priv = ioremap(start, len);
	अगर (!new->mtd.priv) अणु
		pr_err("ioremap failed\n");
		जाओ out1;
	पूर्ण


	new->mtd.name = name;
	new->mtd.size = len;
	new->mtd.flags = MTD_CAP_RAM;
	new->mtd._erase = phram_erase;
	new->mtd._poपूर्णांक = phram_poपूर्णांक;
	new->mtd._unpoपूर्णांक = phram_unpoपूर्णांक;
	new->mtd._पढ़ो = phram_पढ़ो;
	new->mtd._ग_लिखो = phram_ग_लिखो;
	new->mtd.owner = THIS_MODULE;
	new->mtd.type = MTD_RAM;
	new->mtd.erasesize = erasesize;
	new->mtd.ग_लिखोsize = 1;

	ret = -EAGAIN;
	अगर (mtd_device_रेजिस्टर(&new->mtd, शून्य, 0)) अणु
		pr_err("Failed to register new device\n");
		जाओ out2;
	पूर्ण

	list_add_tail(&new->list, &phram_list);
	वापस 0;

out2:
	iounmap(new->mtd.priv);
out1:
	kमुक्त(new);
out0:
	वापस ret;
पूर्ण

अटल पूर्णांक parse_num64(uपूर्णांक64_t *num64, अक्षर *token)
अणु
	माप_प्रकार len;
	पूर्णांक shअगरt = 0;
	पूर्णांक ret;

	len = म_माप(token);
	/* By dwmw2 editorial decree, "ki", "Mi" or "Gi" are to be used. */
	अगर (len > 2) अणु
		अगर (token[len - 1] == 'i') अणु
			चयन (token[len - 2]) अणु
			हाल 'G':
				shअगरt += 10;
				fallthrough;
			हाल 'M':
				shअगरt += 10;
				fallthrough;
			हाल 'k':
				shअगरt += 10;
				token[len - 2] = 0;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = kstrtou64(token, 0, num64);
	*num64 <<= shअगरt;

	वापस ret;
पूर्ण

अटल पूर्णांक parse_name(अक्षर **pname, स्थिर अक्षर *token)
अणु
	माप_प्रकार len;
	अक्षर *name;

	len = म_माप(token) + 1;
	अगर (len > 64)
		वापस -ENOSPC;

	name = kstrdup(token, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	*pname = name;
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम समाप्त_final_newline(अक्षर *str)
अणु
	अक्षर *newline = म_खोजप(str, '\n');

	अगर (newline && !newline[1])
		*newline = 0;
पूर्ण


#घोषणा parse_err(fmt, args...) करो अणु	\
	pr_err(fmt , ## args);	\
	वापस 1;		\
पूर्ण जबतक (0)

#अगर_अघोषित MODULE
अटल पूर्णांक phram_init_called;
/*
 * This shall contain the module parameter अगर any. It is of the क्रमm:
 * - phram=<device>,<address>,<size>[,<erasesize>] क्रम module हाल
 * - phram.phram=<device>,<address>,<size>[,<erasesize>] क्रम built-in हाल
 * We leave 64 bytes क्रम the device name, 20 क्रम the address , 20 क्रम the
 * size and 20 क्रम the erasesize.
 * Example: phram.phram=rootfs,0xa0000000,512Mi,65536
 */
अटल अक्षर phram_paramline[64 + 20 + 20 + 20];
#पूर्ण_अगर

अटल पूर्णांक phram_setup(स्थिर अक्षर *val)
अणु
	अक्षर buf[64 + 20 + 20 + 20], *str = buf;
	अक्षर *token[4];
	अक्षर *name;
	uपूर्णांक64_t start;
	uपूर्णांक64_t len;
	uपूर्णांक64_t erasesize = PAGE_SIZE;
	uपूर्णांक32_t rem;
	पूर्णांक i, ret;

	अगर (strnlen(val, माप(buf)) >= माप(buf))
		parse_err("parameter too long\n");

	म_नकल(str, val);
	समाप्त_final_newline(str);

	क्रम (i = 0; i < 4; i++)
		token[i] = strsep(&str, ",");

	अगर (str)
		parse_err("too many arguments\n");

	अगर (!token[2])
		parse_err("not enough arguments\n");

	ret = parse_name(&name, token[0]);
	अगर (ret)
		वापस ret;

	ret = parse_num64(&start, token[1]);
	अगर (ret) अणु
		parse_err("illegal start address\n");
		जाओ error;
	पूर्ण

	ret = parse_num64(&len, token[2]);
	अगर (ret) अणु
		parse_err("illegal device length\n");
		जाओ error;
	पूर्ण

	अगर (token[3]) अणु
		ret = parse_num64(&erasesize, token[3]);
		अगर (ret) अणु
			parse_err("illegal erasesize\n");
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (erasesize)
		भाग_u64_rem(len, (uपूर्णांक32_t)erasesize, &rem);

	अगर (len == 0 || erasesize == 0 || erasesize > len
	    || erasesize > अच_पूर्णांक_उच्च || rem) अणु
		parse_err("illegal erasesize or len\n");
		जाओ error;
	पूर्ण

	ret = रेजिस्टर_device(name, start, len, (uपूर्णांक32_t)erasesize);
	अगर (ret)
		जाओ error;

	pr_info("%s device: %#llx at %#llx for erasesize %#llx\n", name, len, start, erasesize);
	वापस 0;

error:
	kमुक्त(name);
	वापस ret;
पूर्ण

अटल पूर्णांक phram_param_call(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
#अगर_घोषित MODULE
	वापस phram_setup(val);
#अन्यथा
	/*
	 * If more parameters are later passed in via
	 * /sys/module/phram/parameters/phram
	 * and init_phram() has alपढ़ोy been called,
	 * we can parse the argument now.
	 */

	अगर (phram_init_called)
		वापस phram_setup(val);

	/*
	 * During early boot stage, we only save the parameters
	 * here. We must parse them later: अगर the param passed
	 * from kernel boot command line, phram_param_call() is
	 * called so early that it is not possible to resolve
	 * the device (even kदो_स्मृति() fails). Defer that work to
	 * phram_setup().
	 */

	अगर (म_माप(val) >= माप(phram_paramline))
		वापस -ENOSPC;
	म_नकल(phram_paramline, val);

	वापस 0;
#पूर्ण_अगर
पूर्ण

module_param_call(phram, phram_param_call, शून्य, शून्य, 0200);
MODULE_PARM_DESC(phram, "Memory region to map. \"phram=<name>,<start>,<length>[,<erasesize>]\"");


अटल पूर्णांक __init init_phram(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_अघोषित MODULE
	अगर (phram_paramline[0])
		ret = phram_setup(phram_paramline);
	phram_init_called = 1;
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_phram(व्योम)
अणु
	unरेजिस्टर_devices();
पूर्ण

module_init(init_phram);
module_निकास(cleanup_phram);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joern Engel <joern@wh.fh-wedel.de>");
MODULE_DESCRIPTION("MTD driver for physical RAM");
