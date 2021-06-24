<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * /proc/bus/pnp पूर्णांकerface क्रम Plug and Play devices
 *
 * Written by David Hinds, dahinds@users.sourceक्रमge.net
 * Modअगरied by Thomas Hood
 *
 * The .../devices and .../<node> and .../boot/<node> files are
 * utilized by the lspnp and setpnp utilities, supplied with the
 * pcmcia-cs package.
 *     http://pcmcia-cs.sourceक्रमge.net
 *
 * The .../escd file is utilized by the lsescd utility written by
 * Gunther Mayer.
 *
 * The .../legacy_device_resources file is not used yet.
 *
 * The other files are human-पढ़ोable.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pnp.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>

#समावेश <linux/uaccess.h>

#समावेश "pnpbios.h"

अटल काष्ठा proc_dir_entry *proc_pnp = शून्य;
अटल काष्ठा proc_dir_entry *proc_pnp_boot = शून्य;

अटल पूर्णांक pnpconfig_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pnp_isa_config_struc pnps;

	अगर (pnp_bios_isapnp_config(&pnps))
		वापस -EIO;
	seq_म_लिखो(m, "structure_revision %d\n"
		      "number_of_CSNs %d\n"
		      "ISA_read_data_port 0x%x\n",
		   pnps.revision, pnps.no_csns, pnps.isa_rd_data_port);
	वापस 0;
पूर्ण

अटल पूर्णांक escd_info_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा escd_info_struc escd;

	अगर (pnp_bios_escd_info(&escd))
		वापस -EIO;
	seq_म_लिखो(m, "min_ESCD_write_size %d\n"
			"ESCD_size %d\n"
			"NVRAM_base 0x%x\n",
			escd.min_escd_ग_लिखो_size,
			escd.escd_size, escd.nv_storage_base);
	वापस 0;
पूर्ण

#घोषणा MAX_SANE_ESCD_SIZE (32*1024)
अटल पूर्णांक escd_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा escd_info_struc escd;
	अक्षर *पंचांगpbuf;
	पूर्णांक escd_size;

	अगर (pnp_bios_escd_info(&escd))
		वापस -EIO;

	/* sanity check */
	अगर (escd.escd_size > MAX_SANE_ESCD_SIZE) अणु
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: ESCD size reported by BIOS escd_info call is too great\n", __func__);
		वापस -EFBIG;
	पूर्ण

	पंचांगpbuf = kzalloc(escd.escd_size, GFP_KERNEL);
	अगर (!पंचांगpbuf)
		वापस -ENOMEM;

	अगर (pnp_bios_पढ़ो_escd(पंचांगpbuf, escd.nv_storage_base)) अणु
		kमुक्त(पंचांगpbuf);
		वापस -EIO;
	पूर्ण

	escd_size =
	    (अचिन्हित अक्षर)(पंचांगpbuf[0]) + (अचिन्हित अक्षर)(पंचांगpbuf[1]) * 256;

	/* sanity check */
	अगर (escd_size > MAX_SANE_ESCD_SIZE) अणु
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: ESCD size reported by"
				" BIOS read_escd call is too great\n", __func__);
		kमुक्त(पंचांगpbuf);
		वापस -EFBIG;
	पूर्ण

	seq_ग_लिखो(m, पंचांगpbuf, escd_size);
	kमुक्त(पंचांगpbuf);
	वापस 0;
पूर्ण

अटल पूर्णांक pnp_legacyres_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	व्योम *buf;

	buf = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (pnp_bios_get_stat_res(buf)) अणु
		kमुक्त(buf);
		वापस -EIO;
	पूर्ण

	seq_ग_लिखो(m, buf, 65536);
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक pnp_devices_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pnp_bios_node *node;
	u8 nodक्रमागत;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	क्रम (nodक्रमागत = 0; nodक्रमागत < 0xff;) अणु
		u8 thisnodक्रमागत = nodक्रमागत;

		अगर (pnp_bios_get_dev_node(&nodक्रमागत, PNPMODE_DYNAMIC, node))
			अवरोध;
		seq_म_लिखो(m, "%02x\t%08x\t%3phC\t%04x\n",
			     node->handle, node->eisa_id,
			     node->type_code, node->flags);
		अगर (nodक्रमागत <= thisnodक्रमागत) अणु
			prपूर्णांकk(KERN_ERR
			       "%s Node number 0x%x is out of sequence following node 0x%x. Aborting.\n",
			       "PnPBIOS: proc_read_devices:",
			       (अचिन्हित पूर्णांक)nodक्रमागत,
			       (अचिन्हित पूर्णांक)thisnodक्रमागत);
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(node);
	वापस 0;
पूर्ण

अटल पूर्णांक pnpbios_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	व्योम *data = m->निजी;
	काष्ठा pnp_bios_node *node;
	पूर्णांक boot = (दीर्घ)data >> 8;
	u8 nodक्रमागत = (दीर्घ)data;
	पूर्णांक len;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;
	अगर (pnp_bios_get_dev_node(&nodक्रमागत, boot, node)) अणु
		kमुक्त(node);
		वापस -EIO;
	पूर्ण
	len = node->size - माप(काष्ठा pnp_bios_node);
	seq_ग_लिखो(m, node->data, len);
	kमुक्त(node);
	वापस 0;
पूर्ण

अटल पूर्णांक pnpbios_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pnpbios_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार pnpbios_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *pos)
अणु
	व्योम *data = PDE_DATA(file_inode(file));
	काष्ठा pnp_bios_node *node;
	पूर्णांक boot = (दीर्घ)data >> 8;
	u8 nodक्रमागत = (दीर्घ)data;
	पूर्णांक ret = count;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;
	अगर (pnp_bios_get_dev_node(&nodक्रमागत, boot, node)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	अगर (count != node->size - माप(काष्ठा pnp_bios_node)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (copy_from_user(node->data, buf, count)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (pnp_bios_set_dev_node(node->handle, boot, node) != 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = count;
out:
	kमुक्त(node);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops pnpbios_proc_ops = अणु
	.proc_खोलो	= pnpbios_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= pnpbios_proc_ग_लिखो,
पूर्ण;

पूर्णांक pnpbios_पूर्णांकerface_attach_device(काष्ठा pnp_bios_node *node)
अणु
	अक्षर name[3];

	प्र_लिखो(name, "%02x", node->handle);

	अगर (!proc_pnp)
		वापस -EIO;
	अगर (!pnpbios_करोnt_use_current_config) अणु
		proc_create_data(name, 0644, proc_pnp, &pnpbios_proc_ops,
				 (व्योम *)(दीर्घ)(node->handle));
	पूर्ण

	अगर (!proc_pnp_boot)
		वापस -EIO;
	अगर (proc_create_data(name, 0644, proc_pnp_boot, &pnpbios_proc_ops,
			     (व्योम *)(दीर्घ)(node->handle + 0x100)))
		वापस 0;
	वापस -EIO;
पूर्ण

/*
 * When this is called, pnpbios functions are assumed to
 * work and the pnpbios_करोnt_use_current_config flag
 * should alपढ़ोy have been set to the appropriate value
 */
पूर्णांक __init pnpbios_proc_init(व्योम)
अणु
	proc_pnp = proc_सूची_गढ़ो("bus/pnp", शून्य);
	अगर (!proc_pnp)
		वापस -EIO;
	proc_pnp_boot = proc_सूची_गढ़ो("boot", proc_pnp);
	अगर (!proc_pnp_boot)
		वापस -EIO;
	proc_create_single("devices", 0, proc_pnp, pnp_devices_proc_show);
	proc_create_single("configuration_info", 0, proc_pnp,
			pnpconfig_proc_show);
	proc_create_single("escd_info", 0, proc_pnp, escd_info_proc_show);
	proc_create_single("escd", S_IRUSR, proc_pnp, escd_proc_show);
	proc_create_single("legacy_device_resources", 0, proc_pnp,
			pnp_legacyres_proc_show);
	वापस 0;
पूर्ण

व्योम __निकास pnpbios_proc_निकास(व्योम)
अणु
	पूर्णांक i;
	अक्षर name[3];

	अगर (!proc_pnp)
		वापस;

	क्रम (i = 0; i < 0xff; i++) अणु
		प्र_लिखो(name, "%02x", i);
		अगर (!pnpbios_करोnt_use_current_config)
			हटाओ_proc_entry(name, proc_pnp);
		हटाओ_proc_entry(name, proc_pnp_boot);
	पूर्ण
	हटाओ_proc_entry("legacy_device_resources", proc_pnp);
	हटाओ_proc_entry("escd", proc_pnp);
	हटाओ_proc_entry("escd_info", proc_pnp);
	हटाओ_proc_entry("configuration_info", proc_pnp);
	हटाओ_proc_entry("devices", proc_pnp);
	हटाओ_proc_entry("boot", proc_pnp);
	हटाओ_proc_entry("bus/pnp", शून्य);
पूर्ण
