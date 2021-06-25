<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV SCOM bus debugfs पूर्णांकerface
 *
 * Copyright 2010 Benjamin Herrenschmidt, IBM Corp
 *                <benh@kernel.crashing.org>
 *     and        David Gibson, IBM Corporation.
 * Copyright 2013 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/bug.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/prom.h>

अटल u64 opal_scom_unmangle(u64 addr)
अणु
	u64 पंचांगp;

	/*
	 * XSCOM addresses use the top nibble to set indirect mode and
	 * its क्रमm.  Bits 4-11 are always 0.
	 *
	 * Because the debugfs पूर्णांकerface uses चिन्हित offsets and shअगरts
	 * the address left by 3, we basically cannot use the top 4 bits
	 * of the 64-bit address, and thus cannot use the indirect bit.
	 *
	 * To deal with that, we support the indirect bits being in
	 * bits 4-7 (IBM notation) instead of bit 0-3 in this API, we
	 * करो the conversion here.
	 *
	 * For in-kernel use, we करोn't need to करो this mangling.  In
	 * kernel won't have bits 4-7 set.
	 *
	 * So:
	 *   debugfs will always   set 0-3 = 0 and clear 4-7
	 *    kernel will always clear 0-3 = 0 and   set 4-7
	 */
	पंचांगp = addr;
	पंचांगp  &= 0x0f00000000000000;
	addr &= 0xf0ffffffffffffff;
	addr |= पंचांगp << 4;

	वापस addr;
पूर्ण

अटल पूर्णांक opal_scom_पढ़ो(uपूर्णांक32_t chip, uपूर्णांक64_t addr, u64 reg, u64 *value)
अणु
	पूर्णांक64_t rc;
	__be64 v;

	reg = opal_scom_unmangle(addr + reg);
	rc = opal_xscom_पढ़ो(chip, reg, (__be64 *)__pa(&v));
	अगर (rc) अणु
		*value = 0xfffffffffffffffful;
		वापस -EIO;
	पूर्ण
	*value = be64_to_cpu(v);
	वापस 0;
पूर्ण

अटल पूर्णांक opal_scom_ग_लिखो(uपूर्णांक32_t chip, uपूर्णांक64_t addr, u64 reg, u64 value)
अणु
	पूर्णांक64_t rc;

	reg = opal_scom_unmangle(addr + reg);
	rc = opal_xscom_ग_लिखो(chip, reg, value);
	अगर (rc)
		वापस -EIO;
	वापस 0;
पूर्ण

काष्ठा scom_debug_entry अणु
	u32 chip;
	काष्ठा debugfs_blob_wrapper path;
	अक्षर name[16];
पूर्ण;

अटल sमाप_प्रकार scom_debug_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा scom_debug_entry *ent = filp->निजी_data;
	u64 __user *ubuf64 = (u64 __user *)ubuf;
	loff_t off = *ppos;
	sमाप_प्रकार करोne = 0;
	u64 reg, reg_base, reg_cnt, val;
	पूर्णांक rc;

	अगर (off < 0 || (off & 7) || (count & 7))
		वापस -EINVAL;
	reg_base = off >> 3;
	reg_cnt = count >> 3;

	क्रम (reg = 0; reg < reg_cnt; reg++) अणु
		rc = opal_scom_पढ़ो(ent->chip, reg_base, reg, &val);
		अगर (!rc)
			rc = put_user(val, ubuf64);
		अगर (rc) अणु
			अगर (!करोne)
				करोne = rc;
			अवरोध;
		पूर्ण
		ubuf64++;
		*ppos += 8;
		करोne += 8;
	पूर्ण
	वापस करोne;
पूर्ण

अटल sमाप_प्रकार scom_debug_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा scom_debug_entry *ent = filp->निजी_data;
	u64 __user *ubuf64 = (u64 __user *)ubuf;
	loff_t off = *ppos;
	sमाप_प्रकार करोne = 0;
	u64 reg, reg_base, reg_cnt, val;
	पूर्णांक rc;

	अगर (off < 0 || (off & 7) || (count & 7))
		वापस -EINVAL;
	reg_base = off >> 3;
	reg_cnt = count >> 3;

	क्रम (reg = 0; reg < reg_cnt; reg++) अणु
		rc = get_user(val, ubuf64);
		अगर (!rc)
			rc = opal_scom_ग_लिखो(ent->chip, reg_base, reg,  val);
		अगर (rc) अणु
			अगर (!करोne)
				करोne = rc;
			अवरोध;
		पूर्ण
		ubuf64++;
		करोne += 8;
	पूर्ण
	वापस करोne;
पूर्ण

अटल स्थिर काष्ठा file_operations scom_debug_fops = अणु
	.पढ़ो =		scom_debug_पढ़ो,
	.ग_लिखो =	scom_debug_ग_लिखो,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल पूर्णांक scom_debug_init_one(काष्ठा dentry *root, काष्ठा device_node *dn,
			       पूर्णांक chip)
अणु
	काष्ठा scom_debug_entry *ent;
	काष्ठा dentry *dir;

	ent = kzalloc(माप(*ent), GFP_KERNEL);
	अगर (!ent)
		वापस -ENOMEM;

	ent->chip = chip;
	snम_लिखो(ent->name, 16, "%08x", chip);
	ent->path.data = (व्योम *)kaप्र_लिखो(GFP_KERNEL, "%pOF", dn);
	ent->path.size = म_माप((अक्षर *)ent->path.data);

	dir = debugfs_create_dir(ent->name, root);
	अगर (!dir) अणु
		kमुक्त(ent->path.data);
		kमुक्त(ent);
		वापस -1;
	पूर्ण

	debugfs_create_blob("devspec", 0400, dir, &ent->path);
	debugfs_create_file("access", 0600, dir, ent, &scom_debug_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक scom_debug_init(व्योम)
अणु
	काष्ठा device_node *dn;
	काष्ठा dentry *root;
	पूर्णांक chip, rc;

	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस 0;

	root = debugfs_create_dir("scom", घातerpc_debugfs_root);
	अगर (!root)
		वापस -1;

	rc = 0;
	क्रम_each_node_with_property(dn, "scom-controller") अणु
		chip = of_get_ibm_chip_id(dn);
		WARN_ON(chip == -1);
		rc |= scom_debug_init_one(root, dn, chip);
	पूर्ण

	वापस rc;
पूर्ण
device_initcall(scom_debug_init);
