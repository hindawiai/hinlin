<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rtas.h>

#समावेश "cxl.h"
#समावेश "hcalls.h"

#घोषणा DOWNLOAD_IMAGE 1
#घोषणा VALIDATE_IMAGE 2

काष्ठा ai_header अणु
	u16 version;
	u8  reserved0[6];
	u16 venकरोr;
	u16 device;
	u16 subप्रणाली_venकरोr;
	u16 subप्रणाली;
	u64 image_offset;
	u64 image_length;
	u8  reserved1[96];
पूर्ण;

अटल काष्ठा semaphore sem;
अटल अचिन्हित दीर्घ *buffer[CXL_AI_MAX_ENTRIES];
अटल काष्ठा sg_list *le;
अटल u64 जारी_token;
अटल अचिन्हित पूर्णांक transfer;

काष्ठा update_props_workarea अणु
	__be32 phandle;
	__be32 state;
	__be64 reserved;
	__be32 nprops;
पूर्ण __packed;

काष्ठा update_nodes_workarea अणु
	__be32 state;
	__be64 unit_address;
	__be32 reserved;
पूर्ण __packed;

#घोषणा DEVICE_SCOPE 3
#घोषणा NODE_ACTION_MASK	0xff000000
#घोषणा NODE_COUNT_MASK		0x00ffffff
#घोषणा OPCODE_DELETE	0x01000000
#घोषणा OPCODE_UPDATE	0x02000000
#घोषणा OPCODE_ADD	0x03000000

अटल पूर्णांक rcall(पूर्णांक token, अक्षर *buf, s32 scope)
अणु
	पूर्णांक rc;

	spin_lock(&rtas_data_buf_lock);

	स_नकल(rtas_data_buf, buf, RTAS_DATA_BUF_SIZE);
	rc = rtas_call(token, 2, 1, शून्य, rtas_data_buf, scope);
	स_नकल(buf, rtas_data_buf, RTAS_DATA_BUF_SIZE);

	spin_unlock(&rtas_data_buf_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक update_property(काष्ठा device_node *dn, स्थिर अक्षर *name,
			   u32 vd, अक्षर *value)
अणु
	काष्ठा property *new_prop;
	u32 *val;
	पूर्णांक rc;

	new_prop = kzalloc(माप(*new_prop), GFP_KERNEL);
	अगर (!new_prop)
		वापस -ENOMEM;

	new_prop->name = kstrdup(name, GFP_KERNEL);
	अगर (!new_prop->name) अणु
		kमुक्त(new_prop);
		वापस -ENOMEM;
	पूर्ण

	new_prop->length = vd;
	new_prop->value = kzalloc(new_prop->length, GFP_KERNEL);
	अगर (!new_prop->value) अणु
		kमुक्त(new_prop->name);
		kमुक्त(new_prop);
		वापस -ENOMEM;
	पूर्ण
	स_नकल(new_prop->value, value, vd);

	val = (u32 *)new_prop->value;
	rc = cxl_update_properties(dn, new_prop);
	pr_devel("%pOFn: update property (%s, length: %i, value: %#x)\n",
		  dn, name, vd, be32_to_cpu(*val));

	अगर (rc) अणु
		kमुक्त(new_prop->name);
		kमुक्त(new_prop->value);
		kमुक्त(new_prop);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक update_node(__be32 phandle, s32 scope)
अणु
	काष्ठा update_props_workarea *upwa;
	काष्ठा device_node *dn;
	पूर्णांक i, rc, ret;
	अक्षर *prop_data;
	अक्षर *buf;
	पूर्णांक token;
	u32 nprops;
	u32 vd;

	token = rtas_token("ibm,update-properties");
	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	dn = of_find_node_by_phandle(be32_to_cpu(phandle));
	अगर (!dn) अणु
		kमुक्त(buf);
		वापस -ENOENT;
	पूर्ण

	upwa = (काष्ठा update_props_workarea *)&buf[0];
	upwa->phandle = phandle;
	करो अणु
		rc = rcall(token, buf, scope);
		अगर (rc < 0)
			अवरोध;

		prop_data = buf + माप(*upwa);
		nprops = be32_to_cpu(upwa->nprops);

		अगर (*prop_data == 0) अणु
			prop_data++;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += vd + माप(vd);
			nprops--;
		पूर्ण

		क्रम (i = 0; i < nprops; i++) अणु
			अक्षर *prop_name;

			prop_name = prop_data;
			prop_data += म_माप(prop_name) + 1;
			vd = be32_to_cpu(*(__be32 *)prop_data);
			prop_data += माप(vd);

			अगर ((vd != 0x00000000) && (vd != 0x80000000)) अणु
				ret = update_property(dn, prop_name, vd,
						prop_data);
				अगर (ret)
					pr_err("cxl: Could not update property %s - %i\n",
					       prop_name, ret);

				prop_data += vd;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (rc == 1);

	of_node_put(dn);
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक update_devicetree(काष्ठा cxl *adapter, s32 scope)
अणु
	काष्ठा update_nodes_workarea *unwa;
	u32 action, node_count;
	पूर्णांक token, rc, i;
	__be32 *data, phandle;
	अक्षर *buf;

	token = rtas_token("ibm,update-nodes");
	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	buf = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	unwa = (काष्ठा update_nodes_workarea *)&buf[0];
	unwa->unit_address = cpu_to_be64(adapter->guest->handle);
	करो अणु
		rc = rcall(token, buf, scope);
		अगर (rc && rc != 1)
			अवरोध;

		data = (__be32 *)buf + 4;
		जबतक (be32_to_cpu(*data) & NODE_ACTION_MASK) अणु
			action = be32_to_cpu(*data) & NODE_ACTION_MASK;
			node_count = be32_to_cpu(*data) & NODE_COUNT_MASK;
			pr_devel("device reconfiguration - action: %#x, nodes: %#x\n",
				 action, node_count);
			data++;

			क्रम (i = 0; i < node_count; i++) अणु
				phandle = *data++;

				चयन (action) अणु
				हाल OPCODE_DELETE:
					/* nothing to करो */
					अवरोध;
				हाल OPCODE_UPDATE:
					update_node(phandle, scope);
					अवरोध;
				हाल OPCODE_ADD:
					/* nothing to करो, just move poपूर्णांकer */
					data++;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक (rc == 1);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक handle_image(काष्ठा cxl *adapter, पूर्णांक operation,
			दीर्घ (*fct)(u64, u64, u64, u64 *),
			काष्ठा cxl_adapter_image *ai)
अणु
	माप_प्रकार mod, s_copy, len_chunk = 0;
	काष्ठा ai_header *header = शून्य;
	अचिन्हित पूर्णांक entries = 0, i;
	व्योम *dest, *from;
	पूर्णांक rc = 0, need_header;

	/* base adapter image header */
	need_header = (ai->flags & CXL_AI_NEED_HEADER);
	अगर (need_header) अणु
		header = kzalloc(माप(काष्ठा ai_header), GFP_KERNEL);
		अगर (!header)
			वापस -ENOMEM;
		header->version = cpu_to_be16(1);
		header->venकरोr = cpu_to_be16(adapter->guest->venकरोr);
		header->device = cpu_to_be16(adapter->guest->device);
		header->subप्रणाली_venकरोr = cpu_to_be16(adapter->guest->subप्रणाली_venकरोr);
		header->subप्रणाली = cpu_to_be16(adapter->guest->subप्रणाली);
		header->image_offset = cpu_to_be64(CXL_AI_HEADER_SIZE);
		header->image_length = cpu_to_be64(ai->len_image);
	पूर्ण

	/* number of entries in the list */
	len_chunk = ai->len_data;
	अगर (need_header)
		len_chunk += CXL_AI_HEADER_SIZE;

	entries = len_chunk / CXL_AI_BUFFER_SIZE;
	mod = len_chunk % CXL_AI_BUFFER_SIZE;
	अगर (mod)
		entries++;

	अगर (entries > CXL_AI_MAX_ENTRIES) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	/*          < -- MAX_CHUNK_SIZE = 4096 * 256 = 1048576 bytes -->
	 * chunk 0  ----------------------------------------------------
	 *          | header   |  data                                 |
	 *          ----------------------------------------------------
	 * chunk 1  ----------------------------------------------------
	 *          | data                                             |
	 *          ----------------------------------------------------
	 * ....
	 * chunk n  ----------------------------------------------------
	 *          | data                                             |
	 *          ----------------------------------------------------
	 */
	from = (व्योम *) ai->data;
	क्रम (i = 0; i < entries; i++) अणु
		dest = buffer[i];
		s_copy = CXL_AI_BUFFER_SIZE;

		अगर ((need_header) && (i == 0)) अणु
			/* add adapter image header */
			स_नकल(buffer[i], header, माप(काष्ठा ai_header));
			s_copy = CXL_AI_BUFFER_SIZE - CXL_AI_HEADER_SIZE;
			dest += CXL_AI_HEADER_SIZE; /* image offset */
		पूर्ण
		अगर ((i == (entries - 1)) && mod)
			s_copy = mod;

		/* copy data */
		अगर (copy_from_user(dest, from, s_copy))
			जाओ err;

		/* fill in the list */
		le[i].phys_addr = cpu_to_be64(virt_to_phys(buffer[i]));
		le[i].len = cpu_to_be64(CXL_AI_BUFFER_SIZE);
		अगर ((i == (entries - 1)) && mod)
			le[i].len = cpu_to_be64(mod);
		from += s_copy;
	पूर्ण
	pr_devel("%s (op: %i, need header: %i, entries: %i, token: %#llx)\n",
		 __func__, operation, need_header, entries, जारी_token);

	/*
	 * करोwnload/validate the adapter image to the coherent
	 * platक्रमm facility
	 */
	rc = fct(adapter->guest->handle, virt_to_phys(le), entries,
		&जारी_token);
	अगर (rc == 0) /* success of करोwnload/validation operation */
		जारी_token = 0;

err:
	kमुक्त(header);

	वापस rc;
पूर्ण

अटल पूर्णांक transfer_image(काष्ठा cxl *adapter, पूर्णांक operation,
			काष्ठा cxl_adapter_image *ai)
अणु
	पूर्णांक rc = 0;
	पूर्णांक afu;

	चयन (operation) अणु
	हाल DOWNLOAD_IMAGE:
		rc = handle_image(adapter, operation,
				&cxl_h_करोwnload_adapter_image, ai);
		अगर (rc < 0) अणु
			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);
		पूर्ण
		वापस rc;

	हाल VALIDATE_IMAGE:
		rc = handle_image(adapter, operation,
				&cxl_h_validate_adapter_image, ai);
		अगर (rc < 0) अणु
			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);
			वापस rc;
		पूर्ण
		अगर (rc == 0) अणु
			pr_devel("remove current afu\n");
			क्रम (afu = 0; afu < adapter->slices; afu++)
				cxl_guest_हटाओ_afu(adapter->afu[afu]);

			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);

			/* The entire image has now been
			 * करोwnloaded and the validation has
			 * been successfully perक्रमmed.
			 * After that, the partition should call
			 * ibm,update-nodes and
			 * ibm,update-properties to receive the
			 * current configuration
			 */
			rc = update_devicetree(adapter, DEVICE_SCOPE);
			transfer = 1;
		पूर्ण
		वापस rc;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ ioctl_transfer_image(काष्ठा cxl *adapter, पूर्णांक operation,
				काष्ठा cxl_adapter_image __user *uai)
अणु
	काष्ठा cxl_adapter_image ai;

	pr_devel("%s\n", __func__);

	अगर (copy_from_user(&ai, uai, माप(काष्ठा cxl_adapter_image)))
		वापस -EFAULT;

	/*
	 * Make sure reserved fields and bits are set to 0
	 */
	अगर (ai.reserved1 || ai.reserved2 || ai.reserved3 || ai.reserved4 ||
		(ai.flags & ~CXL_AI_ALL))
		वापस -EINVAL;

	वापस transfer_image(adapter, operation, &ai);
पूर्ण

अटल पूर्णांक device_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक adapter_num = CXL_DEVT_ADAPTER(inode->i_rdev);
	काष्ठा cxl *adapter;
	पूर्णांक rc = 0, i;

	pr_devel("in %s\n", __func__);

	BUG_ON(माप(काष्ठा ai_header) != CXL_AI_HEADER_SIZE);

	/* Allows one process to खोलो the device by using a semaphore */
	अगर (करोwn_पूर्णांकerruptible(&sem) != 0)
		वापस -EPERM;

	अगर (!(adapter = get_cxl_adapter(adapter_num))) अणु
		rc = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	file->निजी_data = adapter;
	जारी_token = 0;
	transfer = 0;

	क्रम (i = 0; i < CXL_AI_MAX_ENTRIES; i++)
		buffer[i] = शून्य;

	/* aligned buffer containing list entries which describes up to
	 * 1 megabyte of data (256 entries of 4096 bytes each)
	 *  Logical real address of buffer 0  -  Buffer 0 length in bytes
	 *  Logical real address of buffer 1  -  Buffer 1 length in bytes
	 *  Logical real address of buffer 2  -  Buffer 2 length in bytes
	 *  ....
	 *  ....
	 *  Logical real address of buffer N  -  Buffer N length in bytes
	 */
	le = (काष्ठा sg_list *)get_zeroed_page(GFP_KERNEL);
	अगर (!le) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < CXL_AI_MAX_ENTRIES; i++) अणु
		buffer[i] = (अचिन्हित दीर्घ *)get_zeroed_page(GFP_KERNEL);
		अगर (!buffer[i]) अणु
			rc = -ENOMEM;
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	क्रम (i = 0; i < CXL_AI_MAX_ENTRIES; i++) अणु
		अगर (buffer[i])
			मुक्त_page((अचिन्हित दीर्घ) buffer[i]);
	पूर्ण

	अगर (le)
		मुक्त_page((अचिन्हित दीर्घ) le);
err:
	put_device(&adapter->dev);
err_unlock:
	up(&sem);

	वापस rc;
पूर्ण

अटल दीर्घ device_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cxl *adapter = file->निजी_data;

	pr_devel("in %s\n", __func__);

	अगर (cmd == CXL_IOCTL_DOWNLOAD_IMAGE)
		वापस ioctl_transfer_image(adapter,
					DOWNLOAD_IMAGE,
					(काष्ठा cxl_adapter_image __user *)arg);
	अन्यथा अगर (cmd == CXL_IOCTL_VALIDATE_IMAGE)
		वापस ioctl_transfer_image(adapter,
					VALIDATE_IMAGE,
					(काष्ठा cxl_adapter_image __user *)arg);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक device_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cxl *adapter = file->निजी_data;
	पूर्णांक i;

	pr_devel("in %s\n", __func__);

	क्रम (i = 0; i < CXL_AI_MAX_ENTRIES; i++) अणु
		अगर (buffer[i])
			मुक्त_page((अचिन्हित दीर्घ) buffer[i]);
	पूर्ण

	अगर (le)
		मुक्त_page((अचिन्हित दीर्घ) le);

	up(&sem);
	put_device(&adapter->dev);
	जारी_token = 0;

	/* reload the module */
	अगर (transfer)
		cxl_guest_reload_module(adapter);
	अन्यथा अणु
		pr_devel("resetting adapter\n");
		cxl_h_reset_adapter(adapter->guest->handle);
	पूर्ण

	transfer = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= device_खोलो,
	.unlocked_ioctl	= device_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.release	= device_बंद,
पूर्ण;

व्योम cxl_guest_हटाओ_अक्षरdev(काष्ठा cxl *adapter)
अणु
	cdev_del(&adapter->guest->cdev);
पूर्ण

पूर्णांक cxl_guest_add_अक्षरdev(काष्ठा cxl *adapter)
अणु
	dev_t devt;
	पूर्णांक rc;

	devt = MKDEV(MAJOR(cxl_get_dev()), CXL_CARD_MINOR(adapter));
	cdev_init(&adapter->guest->cdev, &fops);
	अगर ((rc = cdev_add(&adapter->guest->cdev, devt, 1))) अणु
		dev_err(&adapter->dev,
			"Unable to add chardev on adapter (card%i): %i\n",
			adapter->adapter_num, rc);
		जाओ err;
	पूर्ण
	adapter->dev.devt = devt;
	sema_init(&sem, 1);
err:
	वापस rc;
पूर्ण
