<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*======================================================================

  This driver provides a method to access memory not used by the kernel
  itself (i.e. अगर the kernel commandline mem=xxx is used). To actually
  use slram at least mtdblock or mtdअक्षर is required (क्रम block or
  अक्षरacter device access).

  Usage:

  अगर compiled as loadable module:
    modprobe slram map=<name>,<start>,<end/offset>
  अगर अटलally linked पूर्णांकo the kernel use the following kernel cmd.line
    slram=<name>,<start>,<end/offset>

  <name>: name of the device that will be listed in /proc/mtd
  <start>: start of the memory region, decimal or hex (0xabcdef)
  <end/offset>: end of the memory region. It's possible to use +0x1234
                to specअगरy the offset instead of the असलolute address

  NOTE:
  With slram it's only possible to map a contiguous memory region. Thereक्रमe
  अगर there's a device mapped somewhere in the region specअगरied slram will
  fail to load (see kernel log अगर modprobe fails).

  -

  Jochen Schaeuble <psionic@psionic.de>

======================================================================*/


#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <linux/mtd/mtd.h>

#घोषणा SLRAM_MAX_DEVICES_PARAMS 6		/* 3 parameters / device */
#घोषणा SLRAM_BLK_SZ 0x4000

#घोषणा T(fmt, args...) prपूर्णांकk(KERN_DEBUG fmt, ## args)
#घोषणा E(fmt, args...) prपूर्णांकk(KERN_NOTICE fmt, ## args)

प्रकार काष्ठा slram_priv अणु
	u_अक्षर *start;
	u_अक्षर *end;
पूर्ण slram_priv_t;

प्रकार काष्ठा slram_mtd_list अणु
	काष्ठा mtd_info *mtdinfo;
	काष्ठा slram_mtd_list *next;
पूर्ण slram_mtd_list_t;

#अगर_घोषित MODULE
अटल अक्षर *map[SLRAM_MAX_DEVICES_PARAMS];

module_param_array(map, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(map, "List of memory regions to map. \"map=<name>, <start>, <length / end>\"");
#अन्यथा
अटल अक्षर *map;
#पूर्ण_अगर

अटल slram_mtd_list_t *slram_mtdlist = शून्य;

अटल पूर्णांक slram_erase(काष्ठा mtd_info *, काष्ठा erase_info *);
अटल पूर्णांक slram_poपूर्णांक(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, व्योम **,
		resource_माप_प्रकार *);
अटल पूर्णांक slram_unpoपूर्णांक(काष्ठा mtd_info *, loff_t, माप_प्रकार);
अटल पूर्णांक slram_पढ़ो(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक slram_ग_लिखो(काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);

अटल पूर्णांक slram_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	slram_priv_t *priv = mtd->priv;

	स_रखो(priv->start + instr->addr, 0xff, instr->len);

	वापस(0);
पूर्ण

अटल पूर्णांक slram_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	slram_priv_t *priv = mtd->priv;

	*virt = priv->start + from;
	*retlen = len;
	वापस(0);
पूर्ण

अटल पूर्णांक slram_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक slram_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	slram_priv_t *priv = mtd->priv;

	स_नकल(buf, priv->start + from, len);
	*retlen = len;
	वापस(0);
पूर्ण

अटल पूर्णांक slram_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	slram_priv_t *priv = mtd->priv;

	स_नकल(priv->start + to, buf, len);
	*retlen = len;
	वापस(0);
पूर्ण

/*====================================================================*/

अटल पूर्णांक रेजिस्टर_device(अक्षर *name, अचिन्हित दीर्घ start, अचिन्हित दीर्घ length)
अणु
	slram_mtd_list_t **curmtd;

	curmtd = &slram_mtdlist;
	जबतक (*curmtd) अणु
		curmtd = &(*curmtd)->next;
	पूर्ण

	*curmtd = kदो_स्मृति(माप(slram_mtd_list_t), GFP_KERNEL);
	अगर (!(*curmtd)) अणु
		E("slram: Cannot allocate new MTD device.\n");
		वापस(-ENOMEM);
	पूर्ण
	(*curmtd)->mtdinfo = kzalloc(माप(काष्ठा mtd_info), GFP_KERNEL);
	(*curmtd)->next = शून्य;

	अगर ((*curmtd)->mtdinfo)	अणु
		(*curmtd)->mtdinfo->priv =
			kzalloc(माप(slram_priv_t), GFP_KERNEL);

		अगर (!(*curmtd)->mtdinfo->priv) अणु
			kमुक्त((*curmtd)->mtdinfo);
			(*curmtd)->mtdinfo = शून्य;
		पूर्ण
	पूर्ण

	अगर (!(*curmtd)->mtdinfo) अणु
		E("slram: Cannot allocate new MTD device.\n");
		वापस(-ENOMEM);
	पूर्ण

	अगर (!(((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start =
		memremap(start, length,
			 MEMREMAP_WB | MEMREMAP_WT | MEMREMAP_WC))) अणु
		E("slram: memremap failed\n");
		वापस -EIO;
	पूर्ण
	((slram_priv_t *)(*curmtd)->mtdinfo->priv)->end =
		((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start + length;


	(*curmtd)->mtdinfo->name = name;
	(*curmtd)->mtdinfo->size = length;
	(*curmtd)->mtdinfo->flags = MTD_CAP_RAM;
	(*curmtd)->mtdinfo->_erase = slram_erase;
	(*curmtd)->mtdinfo->_poपूर्णांक = slram_poपूर्णांक;
	(*curmtd)->mtdinfo->_unpoपूर्णांक = slram_unpoपूर्णांक;
	(*curmtd)->mtdinfo->_पढ़ो = slram_पढ़ो;
	(*curmtd)->mtdinfo->_ग_लिखो = slram_ग_लिखो;
	(*curmtd)->mtdinfo->owner = THIS_MODULE;
	(*curmtd)->mtdinfo->type = MTD_RAM;
	(*curmtd)->mtdinfo->erasesize = SLRAM_BLK_SZ;
	(*curmtd)->mtdinfo->ग_लिखोsize = 1;

	अगर (mtd_device_रेजिस्टर((*curmtd)->mtdinfo, शून्य, 0))	अणु
		E("slram: Failed to register new device\n");
		memunmap(((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start);
		kमुक्त((*curmtd)->mtdinfo->priv);
		kमुक्त((*curmtd)->mtdinfo);
		वापस(-EAGAIN);
	पूर्ण
	T("slram: Registered device %s from %luKiB to %luKiB\n", name,
			(start / 1024), ((start + length) / 1024));
	T("slram: Mapped from 0x%p to 0x%p\n",
			((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start,
			((slram_priv_t *)(*curmtd)->mtdinfo->priv)->end);
	वापस(0);
पूर्ण

अटल व्योम unरेजिस्टर_devices(व्योम)
अणु
	slram_mtd_list_t *nextitem;

	जबतक (slram_mtdlist) अणु
		nextitem = slram_mtdlist->next;
		mtd_device_unरेजिस्टर(slram_mtdlist->mtdinfo);
		memunmap(((slram_priv_t *)slram_mtdlist->mtdinfo->priv)->start);
		kमुक्त(slram_mtdlist->mtdinfo->priv);
		kमुक्त(slram_mtdlist->mtdinfo);
		kमुक्त(slram_mtdlist);
		slram_mtdlist = nextitem;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ handle_unit(अचिन्हित दीर्घ value, अक्षर *unit)
अणु
	अगर ((*unit == 'M') || (*unit == 'm')) अणु
		वापस(value * 1024 * 1024);
	पूर्ण अन्यथा अगर ((*unit == 'K') || (*unit == 'k')) अणु
		वापस(value * 1024);
	पूर्ण
	वापस(value);
पूर्ण

अटल पूर्णांक parse_cmdline(अक्षर *devname, अक्षर *szstart, अक्षर *szlength)
अणु
	अक्षर *buffer;
	अचिन्हित दीर्घ devstart;
	अचिन्हित दीर्घ devlength;

	अगर ((!devname) || (!szstart) || (!szlength)) अणु
		unरेजिस्टर_devices();
		वापस(-EINVAL);
	पूर्ण

	devstart = simple_म_से_अदीर्घ(szstart, &buffer, 0);
	devstart = handle_unit(devstart, buffer);

	अगर (*(szlength) != '+') अणु
		devlength = simple_म_से_अदीर्घ(szlength, &buffer, 0);
		devlength = handle_unit(devlength, buffer);
		अगर (devlength < devstart)
			जाओ err_out;

		devlength -= devstart;
	पूर्ण अन्यथा अणु
		devlength = simple_म_से_अदीर्घ(szlength + 1, &buffer, 0);
		devlength = handle_unit(devlength, buffer);
	पूर्ण
	T("slram: devname=%s, devstart=0x%lx, devlength=0x%lx\n",
			devname, devstart, devlength);
	अगर (devlength % SLRAM_BLK_SZ != 0)
		जाओ err_out;

	अगर ((devstart = रेजिस्टर_device(devname, devstart, devlength)))अणु
		unरेजिस्टर_devices();
		वापस((पूर्णांक)devstart);
	पूर्ण
	वापस(0);

err_out:
	E("slram: Illegal length parameter.\n");
	वापस(-EINVAL);
पूर्ण

#अगर_अघोषित MODULE

अटल पूर्णांक __init mtd_slram_setup(अक्षर *str)
अणु
	map = str;
	वापस(1);
पूर्ण

__setup("slram=", mtd_slram_setup);

#पूर्ण_अगर

अटल पूर्णांक __init init_slram(व्योम)
अणु
	अक्षर *devname;

#अगर_अघोषित MODULE
	अक्षर *devstart;
	अक्षर *devlength;

	अगर (!map) अणु
		E("slram: not enough parameters.\n");
		वापस(-EINVAL);
	पूर्ण
	जबतक (map) अणु
		devname = devstart = devlength = शून्य;

		अगर (!(devname = strsep(&map, ","))) अणु
			E("slram: No devicename specified.\n");
			अवरोध;
		पूर्ण
		T("slram: devname = %s\n", devname);
		अगर ((!map) || (!(devstart = strsep(&map, ",")))) अणु
			E("slram: No devicestart specified.\n");
		पूर्ण
		T("slram: devstart = %s\n", devstart);
		अगर ((!map) || (!(devlength = strsep(&map, ",")))) अणु
			E("slram: No devicelength / -end specified.\n");
		पूर्ण
		T("slram: devlength = %s\n", devlength);
		अगर (parse_cmdline(devname, devstart, devlength) != 0) अणु
			वापस(-EINVAL);
		पूर्ण
	पूर्ण
#अन्यथा
	पूर्णांक count;
	पूर्णांक i;

	क्रम (count = 0; count < SLRAM_MAX_DEVICES_PARAMS && map[count];
			count++) अणु
	पूर्ण

	अगर ((count % 3 != 0) || (count == 0)) अणु
		E("slram: not enough parameters.\n");
		वापस(-EINVAL);
	पूर्ण
	क्रम (i = 0; i < (count / 3); i++) अणु
		devname = map[i * 3];

		अगर (parse_cmdline(devname, map[i * 3 + 1], map[i * 3 + 2])!=0) अणु
			वापस(-EINVAL);
		पूर्ण

	पूर्ण
#पूर्ण_अगर /* !MODULE */

	वापस(0);
पूर्ण

अटल व्योम __निकास cleanup_slram(व्योम)
अणु
	unरेजिस्टर_devices();
पूर्ण

module_init(init_slram);
module_निकास(cleanup_slram);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jochen Schaeuble <psionic@psionic.de>");
MODULE_DESCRIPTION("MTD driver for uncached system RAM");
