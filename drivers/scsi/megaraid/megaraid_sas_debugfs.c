<शैली गुरु>
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2003-2018  LSI Corporation.
 *  Copyright (c) 2003-2018  Avago Technologies.
 *  Copyright (c) 2003-2018  Broadcom Inc.
 *
 *  This program is मुक्त software; you can redistribute it and/or
 *  modअगरy it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors: Broadcom Inc.
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *           Shivasharan S <shivasharan.srikanteshwara@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compat.h>
#समावेश <linux/irq_poll.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "megaraid_sas_fusion.h"
#समावेश "megaraid_sas.h"

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

काष्ठा dentry *megasas_debugfs_root;

अटल sमाप_प्रकार
megasas_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
		      loff_t *ppos)
अणु
	काष्ठा megasas_debugfs_buffer *debug = filp->निजी_data;

	अगर (!debug || !debug->buf)
		वापस 0;

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, debug->buf, debug->len);
पूर्ण

अटल पूर्णांक
megasas_debugfs_raidmap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा megasas_instance *instance = inode->i_निजी;
	काष्ठा megasas_debugfs_buffer *debug;
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	debug = kzalloc(माप(काष्ठा megasas_debugfs_buffer), GFP_KERNEL);
	अगर (!debug)
		वापस -ENOMEM;

	debug->buf = (व्योम *)fusion->ld_drv_map[(instance->map_id & 1)];
	debug->len = fusion->drv_map_sz;
	file->निजी_data = debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
megasas_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा megasas_debug_buffer *debug = file->निजी_data;

	अगर (!debug)
		वापस 0;

	file->निजी_data = शून्य;
	kमुक्त(debug);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations megasas_debugfs_raidmap_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = megasas_debugfs_raidmap_खोलो,
	.पढ़ो           = megasas_debugfs_पढ़ो,
	.release        = megasas_debugfs_release,
पूर्ण;

/*
 * megasas_init_debugfs :	Create debugfs root क्रम megaraid_sas driver
 */
व्योम megasas_init_debugfs(व्योम)
अणु
	megasas_debugfs_root = debugfs_create_dir("megaraid_sas", शून्य);
	अगर (!megasas_debugfs_root)
		pr_info("Cannot create debugfs root\n");
पूर्ण

/*
 * megasas_निकास_debugfs :	Remove debugfs root क्रम megaraid_sas driver
 */
व्योम megasas_निकास_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(megasas_debugfs_root);
पूर्ण

/*
 * megasas_setup_debugfs :	Setup debugfs per Fusion adapter
 * instance:				Soft instance of adapter
 */
व्योम
megasas_setup_debugfs(काष्ठा megasas_instance *instance)
अणु
	अक्षर name[64];
	काष्ठा fusion_context *fusion;

	fusion = instance->ctrl_context;

	अगर (fusion) अणु
		snम_लिखो(name, माप(name),
			 "scsi_host%d", instance->host->host_no);
		अगर (!instance->debugfs_root) अणु
			instance->debugfs_root =
				debugfs_create_dir(name, megasas_debugfs_root);
			अगर (!instance->debugfs_root) अणु
				dev_err(&instance->pdev->dev,
					"Cannot create per adapter debugfs directory\n");
				वापस;
			पूर्ण
		पूर्ण

		snम_लिखो(name, माप(name), "raidmap_dump");
		instance->raidmap_dump =
			debugfs_create_file(name, S_IRUGO,
					    instance->debugfs_root, instance,
					    &megasas_debugfs_raidmap_fops);
		अगर (!instance->raidmap_dump) अणु
			dev_err(&instance->pdev->dev,
				"Cannot create raidmap debugfs file\n");
			debugfs_हटाओ(instance->debugfs_root);
			वापस;
		पूर्ण
	पूर्ण

पूर्ण

/*
 * megasas_destroy_debugfs :	Destroy debugfs per Fusion adapter
 * instance:					Soft instance of adapter
 */
व्योम megasas_destroy_debugfs(काष्ठा megasas_instance *instance)
अणु
	debugfs_हटाओ_recursive(instance->debugfs_root);
पूर्ण

#अन्यथा
व्योम megasas_init_debugfs(व्योम)
अणु
पूर्ण
व्योम megasas_निकास_debugfs(व्योम)
अणु
पूर्ण
व्योम megasas_setup_debugfs(काष्ठा megasas_instance *instance)
अणु
पूर्ण
व्योम megasas_destroy_debugfs(काष्ठा megasas_instance *instance)
अणु
पूर्ण
#पूर्ण_अगर /*CONFIG_DEBUG_FS*/
