<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Sony MemoryStick Pro storage support
 *
 *  Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 *
 * Special thanks to Carlos Corbacho क्रम providing various MemoryStick cards
 * that made this driver possible.
 */

#समावेश <linux/blk-mq.h>
#समावेश <linux/idr.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/memstick.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME "mspro_block"

अटल पूर्णांक major;
module_param(major, पूर्णांक, 0644);

#घोषणा MSPRO_BLOCK_MAX_SEGS  32
#घोषणा MSPRO_BLOCK_MAX_PAGES ((2 << 16) - 1)

#घोषणा MSPRO_BLOCK_SIGNATURE        0xa5c3
#घोषणा MSPRO_BLOCK_MAX_ATTRIBUTES   41

#घोषणा MSPRO_BLOCK_PART_SHIFT 3

क्रमागत अणु
	MSPRO_BLOCK_ID_SYSINFO         = 0x10,
	MSPRO_BLOCK_ID_MODELNAME       = 0x15,
	MSPRO_BLOCK_ID_MBR             = 0x20,
	MSPRO_BLOCK_ID_PBR16           = 0x21,
	MSPRO_BLOCK_ID_PBR32           = 0x22,
	MSPRO_BLOCK_ID_SPECखाताVALUES1 = 0x25,
	MSPRO_BLOCK_ID_SPECखाताVALUES2 = 0x26,
	MSPRO_BLOCK_ID_DEVINFO         = 0x30
पूर्ण;

काष्ठा mspro_sys_attr अणु
	माप_प्रकार                  size;
	व्योम                    *data;
	अचिन्हित अक्षर           id;
	अक्षर                    name[32];
	काष्ठा device_attribute dev_attr;
पूर्ण;

काष्ठा mspro_attr_entry अणु
	__be32 address;
	__be32 size;
	अचिन्हित अक्षर id;
	अचिन्हित अक्षर reserved[3];
पूर्ण __attribute__((packed));

काष्ठा mspro_attribute अणु
	__be16 signature;
	अचिन्हित लघु          version;
	अचिन्हित अक्षर           count;
	अचिन्हित अक्षर           reserved[11];
	काष्ठा mspro_attr_entry entries[];
पूर्ण __attribute__((packed));

काष्ठा mspro_sys_info अणु
	अचिन्हित अक्षर  class;
	अचिन्हित अक्षर  reserved0;
	__be16 block_size;
	__be16 block_count;
	__be16 user_block_count;
	__be16 page_size;
	अचिन्हित अक्षर  reserved1[2];
	अचिन्हित अक्षर  assembly_date[8];
	__be32 serial_number;
	अचिन्हित अक्षर  assembly_maker_code;
	अचिन्हित अक्षर  assembly_model_code[3];
	__be16 memory_maker_code;
	__be16 memory_model_code;
	अचिन्हित अक्षर  reserved2[4];
	अचिन्हित अक्षर  vcc;
	अचिन्हित अक्षर  vpp;
	__be16 controller_number;
	__be16 controller_function;
	__be16 start_sector;
	__be16 unit_size;
	अचिन्हित अक्षर  ms_sub_class;
	अचिन्हित अक्षर  reserved3[4];
	अचिन्हित अक्षर  पूर्णांकerface_type;
	__be16 controller_code;
	अचिन्हित अक्षर  क्रमmat_type;
	अचिन्हित अक्षर  reserved4;
	अचिन्हित अक्षर  device_type;
	अचिन्हित अक्षर  reserved5[7];
	अचिन्हित अक्षर  mspro_id[16];
	अचिन्हित अक्षर  reserved6[16];
पूर्ण __attribute__((packed));

काष्ठा mspro_mbr अणु
	अचिन्हित अक्षर boot_partition;
	अचिन्हित अक्षर start_head;
	अचिन्हित अक्षर start_sector;
	अचिन्हित अक्षर start_cylinder;
	अचिन्हित अक्षर partition_type;
	अचिन्हित अक्षर end_head;
	अचिन्हित अक्षर end_sector;
	अचिन्हित अक्षर end_cylinder;
	अचिन्हित पूर्णांक  start_sectors;
	अचिन्हित पूर्णांक  sectors_per_partition;
पूर्ण __attribute__((packed));

काष्ठा mspro_specfile अणु
	अक्षर           name[8];
	अक्षर           ext[3];
	अचिन्हित अक्षर  attr;
	अचिन्हित अक्षर  reserved[10];
	अचिन्हित लघु समय;
	अचिन्हित लघु date;
	अचिन्हित लघु cluster;
	अचिन्हित पूर्णांक   size;
पूर्ण __attribute__((packed));

काष्ठा mspro_devinfo अणु
	__be16 cylinders;
	__be16 heads;
	__be16 bytes_per_track;
	__be16 bytes_per_sector;
	__be16 sectors_per_track;
	अचिन्हित अक्षर  reserved[6];
पूर्ण __attribute__((packed));

काष्ठा mspro_block_data अणु
	काष्ठा memstick_dev   *card;
	अचिन्हित पूर्णांक          usage_count;
	अचिन्हित पूर्णांक          caps;
	काष्ठा gendisk        *disk;
	काष्ठा request_queue  *queue;
	काष्ठा request        *block_req;
	काष्ठा blk_mq_tag_set tag_set;
	spinlock_t            q_lock;

	अचिन्हित लघु        page_size;
	अचिन्हित लघु        cylinders;
	अचिन्हित लघु        heads;
	अचिन्हित लघु        sectors_per_track;

	अचिन्हित अक्षर         प्रणाली;
	अचिन्हित अक्षर         पढ़ो_only:1,
			      eject:1,
			      data_dir:1,
			      active:1;
	अचिन्हित अक्षर         transfer_cmd;

	पूर्णांक                   (*mrq_handler)(काष्ठा memstick_dev *card,
					     काष्ठा memstick_request **mrq);


	/* Default request setup function क्रम data access method preferred by
	 * this host instance.
	 */
	व्योम                  (*setup_transfer)(काष्ठा memstick_dev *card,
						u64 offset, माप_प्रकार length);

	काष्ठा attribute_group attr_group;

	काष्ठा scatterlist    req_sg[MSPRO_BLOCK_MAX_SEGS];
	अचिन्हित पूर्णांक          seg_count;
	अचिन्हित पूर्णांक          current_seg;
	अचिन्हित पूर्णांक          current_page;
पूर्ण;

अटल DEFINE_IDR(mspro_block_disk_idr);
अटल DEFINE_MUTEX(mspro_block_disk_lock);

अटल पूर्णांक mspro_block_complete_req(काष्ठा memstick_dev *card, पूर्णांक error);

/*** Block device ***/

अटल पूर्णांक mspro_block_bd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा mspro_block_data *msb = disk->निजी_data;
	पूर्णांक rc = -ENXIO;

	mutex_lock(&mspro_block_disk_lock);

	अगर (msb && msb->card) अणु
		msb->usage_count++;
		अगर ((mode & FMODE_WRITE) && msb->पढ़ो_only)
			rc = -EROFS;
		अन्यथा
			rc = 0;
	पूर्ण

	mutex_unlock(&mspro_block_disk_lock);

	वापस rc;
पूर्ण


अटल व्योम mspro_block_disk_release(काष्ठा gendisk *disk)
अणु
	काष्ठा mspro_block_data *msb = disk->निजी_data;
	पूर्णांक disk_id = MINOR(disk_devt(disk)) >> MSPRO_BLOCK_PART_SHIFT;

	mutex_lock(&mspro_block_disk_lock);

	अगर (msb) अणु
		अगर (msb->usage_count)
			msb->usage_count--;

		अगर (!msb->usage_count) अणु
			kमुक्त(msb);
			disk->निजी_data = शून्य;
			idr_हटाओ(&mspro_block_disk_idr, disk_id);
			put_disk(disk);
		पूर्ण
	पूर्ण

	mutex_unlock(&mspro_block_disk_lock);
पूर्ण

अटल व्योम mspro_block_bd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	mspro_block_disk_release(disk);
पूर्ण

अटल पूर्णांक mspro_block_bd_getgeo(काष्ठा block_device *bdev,
				 काष्ठा hd_geometry *geo)
अणु
	काष्ठा mspro_block_data *msb = bdev->bd_disk->निजी_data;

	geo->heads = msb->heads;
	geo->sectors = msb->sectors_per_track;
	geo->cylinders = msb->cylinders;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations ms_block_bकरोps = अणु
	.खोलो    = mspro_block_bd_खोलो,
	.release = mspro_block_bd_release,
	.getgeo  = mspro_block_bd_getgeo,
	.owner   = THIS_MODULE
पूर्ण;

/*** Inक्रमmation ***/

अटल काष्ठा mspro_sys_attr *mspro_from_sysfs_attr(काष्ठा attribute *attr)
अणु
	काष्ठा device_attribute *dev_attr
		= container_of(attr, काष्ठा device_attribute, attr);
	वापस container_of(dev_attr, काष्ठा mspro_sys_attr, dev_attr);
पूर्ण

अटल स्थिर अक्षर *mspro_block_attr_name(अचिन्हित अक्षर tag)
अणु
	चयन (tag) अणु
	हाल MSPRO_BLOCK_ID_SYSINFO:
		वापस "attr_sysinfo";
	हाल MSPRO_BLOCK_ID_MODELNAME:
		वापस "attr_modelname";
	हाल MSPRO_BLOCK_ID_MBR:
		वापस "attr_mbr";
	हाल MSPRO_BLOCK_ID_PBR16:
		वापस "attr_pbr16";
	हाल MSPRO_BLOCK_ID_PBR32:
		वापस "attr_pbr32";
	हाल MSPRO_BLOCK_ID_SPECखाताVALUES1:
		वापस "attr_specfilevalues1";
	हाल MSPRO_BLOCK_ID_SPECखाताVALUES2:
		वापस "attr_specfilevalues2";
	हाल MSPRO_BLOCK_ID_DEVINFO:
		वापस "attr_devinfo";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

प्रकार sमाप_प्रकार (*sysfs_show_t)(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buffer);

अटल sमाप_प्रकार mspro_block_attr_show_शेष(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *s_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);

	sमाप_प्रकार cnt, rc = 0;

	क्रम (cnt = 0; cnt < s_attr->size; cnt++) अणु
		अगर (cnt && !(cnt % 16)) अणु
			अगर (PAGE_SIZE - rc)
				buffer[rc++] = '\n';
		पूर्ण

		rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "%02x ",
				((अचिन्हित अक्षर *)s_attr->data)[cnt]);
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mspro_block_attr_show_sysinfo(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *x_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);
	काष्ठा mspro_sys_info *x_sys = x_attr->data;
	sमाप_प्रकार rc = 0;
	पूर्णांक date_tz = 0, date_tz_f = 0;

	अगर (x_sys->assembly_date[0] > 0x80U) अणु
		date_tz = (~x_sys->assembly_date[0]) + 1;
		date_tz_f = date_tz & 3;
		date_tz >>= 2;
		date_tz = -date_tz;
		date_tz_f *= 15;
	पूर्ण अन्यथा अगर (x_sys->assembly_date[0] < 0x80U) अणु
		date_tz = x_sys->assembly_date[0];
		date_tz_f = date_tz & 3;
		date_tz >>= 2;
		date_tz_f *= 15;
	पूर्ण

	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "class: %x\n",
			x_sys->class);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "block size: %x\n",
			be16_to_cpu(x_sys->block_size));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "block count: %x\n",
			be16_to_cpu(x_sys->block_count));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "user block count: %x\n",
			be16_to_cpu(x_sys->user_block_count));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "page size: %x\n",
			be16_to_cpu(x_sys->page_size));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "assembly date: "
			"GMT%+d:%d %04u-%02u-%02u %02u:%02u:%02u\n",
			date_tz, date_tz_f,
			be16_to_cpup((__be16 *)&x_sys->assembly_date[1]),
			x_sys->assembly_date[3], x_sys->assembly_date[4],
			x_sys->assembly_date[5], x_sys->assembly_date[6],
			x_sys->assembly_date[7]);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "serial number: %x\n",
			be32_to_cpu(x_sys->serial_number));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc,
			"assembly maker code: %x\n",
			x_sys->assembly_maker_code);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "assembly model code: "
			"%02x%02x%02x\n", x_sys->assembly_model_code[0],
			x_sys->assembly_model_code[1],
			x_sys->assembly_model_code[2]);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "memory maker code: %x\n",
			be16_to_cpu(x_sys->memory_maker_code));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "memory model code: %x\n",
			be16_to_cpu(x_sys->memory_model_code));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "vcc: %x\n",
			x_sys->vcc);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "vpp: %x\n",
			x_sys->vpp);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "controller number: %x\n",
			be16_to_cpu(x_sys->controller_number));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc,
			"controller function: %x\n",
			be16_to_cpu(x_sys->controller_function));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start sector: %x\n",
			be16_to_cpu(x_sys->start_sector));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "unit size: %x\n",
			be16_to_cpu(x_sys->unit_size));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "sub class: %x\n",
			x_sys->ms_sub_class);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "interface type: %x\n",
			x_sys->पूर्णांकerface_type);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "controller code: %x\n",
			be16_to_cpu(x_sys->controller_code));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "format type: %x\n",
			x_sys->क्रमmat_type);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "device type: %x\n",
			x_sys->device_type);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "mspro id: %s\n",
			x_sys->mspro_id);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mspro_block_attr_show_modelname(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *s_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s", (अक्षर *)s_attr->data);
पूर्ण

अटल sमाप_प्रकार mspro_block_attr_show_mbr(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *x_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);
	काष्ठा mspro_mbr *x_mbr = x_attr->data;
	sमाप_प्रकार rc = 0;

	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "boot partition: %x\n",
			x_mbr->boot_partition);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start head: %x\n",
			x_mbr->start_head);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start sector: %x\n",
			x_mbr->start_sector);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start cylinder: %x\n",
			x_mbr->start_cylinder);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "partition type: %x\n",
			x_mbr->partition_type);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "end head: %x\n",
			x_mbr->end_head);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "end sector: %x\n",
			x_mbr->end_sector);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "end cylinder: %x\n",
			x_mbr->end_cylinder);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start sectors: %x\n",
			x_mbr->start_sectors);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc,
			"sectors per partition: %x\n",
			x_mbr->sectors_per_partition);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mspro_block_attr_show_specfile(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *x_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);
	काष्ठा mspro_specfile *x_spfile = x_attr->data;
	अक्षर name[9], ext[4];
	sमाप_प्रकार rc = 0;

	स_नकल(name, x_spfile->name, 8);
	name[8] = 0;
	स_नकल(ext, x_spfile->ext, 3);
	ext[3] = 0;

	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "name: %s\n", name);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "ext: %s\n", ext);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "attribute: %x\n",
			x_spfile->attr);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "time: %d:%d:%d\n",
			x_spfile->समय >> 11,
			(x_spfile->समय >> 5) & 0x3f,
			(x_spfile->समय & 0x1f) * 2);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "date: %d-%d-%d\n",
			(x_spfile->date >> 9) + 1980,
			(x_spfile->date >> 5) & 0xf,
			x_spfile->date & 0x1f);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "start cluster: %x\n",
			x_spfile->cluster);
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "size: %x\n",
			x_spfile->size);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mspro_block_attr_show_devinfo(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buffer)
अणु
	काष्ठा mspro_sys_attr *x_attr = container_of(attr,
						     काष्ठा mspro_sys_attr,
						     dev_attr);
	काष्ठा mspro_devinfo *x_devinfo = x_attr->data;
	sमाप_प्रकार rc = 0;

	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "cylinders: %x\n",
			be16_to_cpu(x_devinfo->cylinders));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "heads: %x\n",
			be16_to_cpu(x_devinfo->heads));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "bytes per track: %x\n",
			be16_to_cpu(x_devinfo->bytes_per_track));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "bytes per sector: %x\n",
			be16_to_cpu(x_devinfo->bytes_per_sector));
	rc += scnम_लिखो(buffer + rc, PAGE_SIZE - rc, "sectors per track: %x\n",
			be16_to_cpu(x_devinfo->sectors_per_track));
	वापस rc;
पूर्ण

अटल sysfs_show_t mspro_block_attr_show(अचिन्हित अक्षर tag)
अणु
	चयन (tag) अणु
	हाल MSPRO_BLOCK_ID_SYSINFO:
		वापस mspro_block_attr_show_sysinfo;
	हाल MSPRO_BLOCK_ID_MODELNAME:
		वापस mspro_block_attr_show_modelname;
	हाल MSPRO_BLOCK_ID_MBR:
		वापस mspro_block_attr_show_mbr;
	हाल MSPRO_BLOCK_ID_SPECखाताVALUES1:
	हाल MSPRO_BLOCK_ID_SPECखाताVALUES2:
		वापस mspro_block_attr_show_specfile;
	हाल MSPRO_BLOCK_ID_DEVINFO:
		वापस mspro_block_attr_show_devinfo;
	शेष:
		वापस mspro_block_attr_show_शेष;
	पूर्ण
पूर्ण

/*** Protocol handlers ***/

/*
 * Functions prefixed with "h_" are protocol callbacks. They can be called from
 * पूर्णांकerrupt context. Return value of 0 means that request processing is still
 * ongoing, जबतक special error value of -EAGAIN means that current request is
 * finished (and request processor should come back some समय later).
 */

अटल पूर्णांक h_mspro_block_req_init(काष्ठा memstick_dev *card,
				  काष्ठा memstick_request **mrq)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	*mrq = &card->current_mrq;
	card->next_request = msb->mrq_handler;
	वापस 0;
पूर्ण

अटल पूर्णांक h_mspro_block_शेष(काष्ठा memstick_dev *card,
				 काष्ठा memstick_request **mrq)
अणु
	वापस mspro_block_complete_req(card, (*mrq)->error);
पूर्ण

अटल पूर्णांक h_mspro_block_शेष_bad(काष्ठा memstick_dev *card,
				     काष्ठा memstick_request **mrq)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक h_mspro_block_get_ro(काष्ठा memstick_dev *card,
				काष्ठा memstick_request **mrq)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	अगर (!(*mrq)->error) अणु
		अगर ((*mrq)->data[दुरत्व(काष्ठा ms_status_रेजिस्टर, status0)]
		    & MEMSTICK_STATUS0_WP)
			msb->पढ़ो_only = 1;
		अन्यथा
			msb->पढ़ो_only = 0;
	पूर्ण

	वापस mspro_block_complete_req(card, (*mrq)->error);
पूर्ण

अटल पूर्णांक h_mspro_block_रुको_क्रम_ced(काष्ठा memstick_dev *card,
				      काष्ठा memstick_request **mrq)
अणु
	dev_dbg(&card->dev, "wait for ced: value %x\n", (*mrq)->data[0]);

	अगर (!(*mrq)->error) अणु
		अगर ((*mrq)->data[0] & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_ERR))
			(*mrq)->error = -EFAULT;
		अन्यथा अगर (!((*mrq)->data[0] & MEMSTICK_INT_CED))
			वापस 0;
	पूर्ण

	वापस mspro_block_complete_req(card, (*mrq)->error);
पूर्ण

अटल पूर्णांक h_mspro_block_transfer_data(काष्ठा memstick_dev *card,
				       काष्ठा memstick_request **mrq)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	अचिन्हित अक्षर t_val = 0;
	काष्ठा scatterlist t_sg = अणु 0 पूर्ण;
	माप_प्रकार t_offset;

	अगर ((*mrq)->error)
		वापस mspro_block_complete_req(card, (*mrq)->error);

	चयन ((*mrq)->tpc) अणु
	हाल MS_TPC_WRITE_REG:
		memstick_init_req(*mrq, MS_TPC_SET_CMD, &msb->transfer_cmd, 1);
		(*mrq)->need_card_पूर्णांक = 1;
		वापस 0;
	हाल MS_TPC_SET_CMD:
		t_val = (*mrq)->पूर्णांक_reg;
		memstick_init_req(*mrq, MS_TPC_GET_INT, शून्य, 1);
		अगर (msb->caps & MEMSTICK_CAP_AUTO_GET_INT)
			जाओ has_पूर्णांक_reg;
		वापस 0;
	हाल MS_TPC_GET_INT:
		t_val = (*mrq)->data[0];
has_पूर्णांक_reg:
		अगर (t_val & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_ERR)) अणु
			t_val = MSPRO_CMD_STOP;
			memstick_init_req(*mrq, MS_TPC_SET_CMD, &t_val, 1);
			card->next_request = h_mspro_block_शेष;
			वापस 0;
		पूर्ण

		अगर (msb->current_page
		    == (msb->req_sg[msb->current_seg].length
			/ msb->page_size)) अणु
			msb->current_page = 0;
			msb->current_seg++;

			अगर (msb->current_seg == msb->seg_count) अणु
				अगर (t_val & MEMSTICK_INT_CED) अणु
					वापस mspro_block_complete_req(card,
									0);
				पूर्ण अन्यथा अणु
					card->next_request
						= h_mspro_block_रुको_क्रम_ced;
					memstick_init_req(*mrq, MS_TPC_GET_INT,
							  शून्य, 1);
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!(t_val & MEMSTICK_INT_BREQ)) अणु
			memstick_init_req(*mrq, MS_TPC_GET_INT, शून्य, 1);
			वापस 0;
		पूर्ण

		t_offset = msb->req_sg[msb->current_seg].offset;
		t_offset += msb->current_page * msb->page_size;

		sg_set_page(&t_sg,
			    nth_page(sg_page(&(msb->req_sg[msb->current_seg])),
				     t_offset >> PAGE_SHIFT),
			    msb->page_size, offset_in_page(t_offset));

		memstick_init_req_sg(*mrq, msb->data_dir == READ
					   ? MS_TPC_READ_LONG_DATA
					   : MS_TPC_WRITE_LONG_DATA,
				     &t_sg);
		(*mrq)->need_card_पूर्णांक = 1;
		वापस 0;
	हाल MS_TPC_READ_LONG_DATA:
	हाल MS_TPC_WRITE_LONG_DATA:
		msb->current_page++;
		अगर (msb->caps & MEMSTICK_CAP_AUTO_GET_INT) अणु
			t_val = (*mrq)->पूर्णांक_reg;
			जाओ has_पूर्णांक_reg;
		पूर्ण अन्यथा अणु
			memstick_init_req(*mrq, MS_TPC_GET_INT, शून्य, 1);
			वापस 0;
		पूर्ण

	शेष:
		BUG();
	पूर्ण
पूर्ण

/*** Transfer setup functions क्रम dअगरferent access methods. ***/

/** Setup data transfer request क्रम SET_CMD TPC with arguments in card
 *  रेजिस्टरs.
 *
 *  @card    Current media instance
 *  @offset  Target data offset in bytes
 *  @length  Required transfer length in bytes.
 */
अटल व्योम h_mspro_block_setup_cmd(काष्ठा memstick_dev *card, u64 offset,
				    माप_प्रकार length)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	काष्ठा mspro_param_रेजिस्टर param = अणु
		.प्रणाली = msb->प्रणाली,
		.data_count = cpu_to_be16((uपूर्णांक16_t)(length / msb->page_size)),
		/* ISO C90 warning precludes direct initialization क्रम now. */
		.data_address = 0,
		.tpc_param = 0
	पूर्ण;

	करो_भाग(offset, msb->page_size);
	param.data_address = cpu_to_be32((uपूर्णांक32_t)offset);

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_transfer_data;
	memstick_init_req(&card->current_mrq, MS_TPC_WRITE_REG,
			  &param, माप(param));
पूर्ण

/*** Data transfer ***/

अटल पूर्णांक mspro_block_issue_req(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	u64 t_off;
	अचिन्हित पूर्णांक count;

	जबतक (true) अणु
		msb->current_page = 0;
		msb->current_seg = 0;
		msb->seg_count = blk_rq_map_sg(msb->block_req->q,
					       msb->block_req,
					       msb->req_sg);

		अगर (!msb->seg_count) अणु
			अचिन्हित पूर्णांक bytes = blk_rq_cur_bytes(msb->block_req);
			bool chunk;

			chunk = blk_update_request(msb->block_req,
							BLK_STS_RESOURCE,
							bytes);
			अगर (chunk)
				जारी;
			__blk_mq_end_request(msb->block_req,
						BLK_STS_RESOURCE);
			msb->block_req = शून्य;
			वापस -EAGAIN;
		पूर्ण

		t_off = blk_rq_pos(msb->block_req);
		t_off <<= 9;
		count = blk_rq_bytes(msb->block_req);

		msb->setup_transfer(card, t_off, count);

		msb->data_dir = rq_data_dir(msb->block_req);
		msb->transfer_cmd = msb->data_dir == READ
				    ? MSPRO_CMD_READ_DATA
				    : MSPRO_CMD_WRITE_DATA;

		memstick_new_req(card->host);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mspro_block_complete_req(काष्ठा memstick_dev *card, पूर्णांक error)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	पूर्णांक cnt;
	bool chunk;
	अचिन्हित पूर्णांक t_len = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msb->q_lock, flags);
	dev_dbg(&card->dev, "complete %d, %d\n", msb->block_req ? 1 : 0,
		error);

	अगर (msb->block_req) अणु
		/* Nothing to करो - not really an error */
		अगर (error == -EAGAIN)
			error = 0;

		अगर (error || (card->current_mrq.tpc == MSPRO_CMD_STOP)) अणु
			अगर (msb->data_dir == READ) अणु
				क्रम (cnt = 0; cnt < msb->current_seg; cnt++) अणु
					t_len += msb->req_sg[cnt].length
						 / msb->page_size;

					अगर (msb->current_page)
						t_len += msb->current_page - 1;

					t_len *= msb->page_size;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			t_len = blk_rq_bytes(msb->block_req);

		dev_dbg(&card->dev, "transferred %x (%d)\n", t_len, error);

		अगर (error && !t_len)
			t_len = blk_rq_cur_bytes(msb->block_req);

		chunk = blk_update_request(msb->block_req,
				त्रुटि_सं_to_blk_status(error), t_len);
		अगर (chunk) अणु
			error = mspro_block_issue_req(card);
			अगर (!error)
				जाओ out;
		पूर्ण अन्यथा अणु
			__blk_mq_end_request(msb->block_req,
						त्रुटि_सं_to_blk_status(error));
			msb->block_req = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!error)
			error = -EAGAIN;
	पूर्ण

	card->next_request = h_mspro_block_शेष_bad;
	complete_all(&card->mrq_complete);
out:
	spin_unlock_irqrestore(&msb->q_lock, flags);
	वापस error;
पूर्ण

अटल व्योम mspro_block_stop(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		spin_lock_irqsave(&msb->q_lock, flags);
		अगर (!msb->block_req) अणु
			blk_mq_stop_hw_queues(msb->queue);
			rc = 1;
		पूर्ण
		spin_unlock_irqrestore(&msb->q_lock, flags);

		अगर (rc)
			अवरोध;

		रुको_क्रम_completion(&card->mrq_complete);
	पूर्ण
पूर्ण

अटल व्योम mspro_block_start(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	blk_mq_start_hw_queues(msb->queue);
पूर्ण

अटल blk_status_t mspro_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				   स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा memstick_dev *card = hctx->queue->queuedata;
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	spin_lock_irq(&msb->q_lock);

	अगर (msb->block_req) अणु
		spin_unlock_irq(&msb->q_lock);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण

	अगर (msb->eject) अणु
		spin_unlock_irq(&msb->q_lock);
		blk_mq_start_request(bd->rq);
		वापस BLK_STS_IOERR;
	पूर्ण

	msb->block_req = bd->rq;
	blk_mq_start_request(bd->rq);

	अगर (mspro_block_issue_req(card))
		msb->block_req = शून्य;

	spin_unlock_irq(&msb->q_lock);
	वापस BLK_STS_OK;
पूर्ण

/*** Initialization ***/

अटल पूर्णांक mspro_block_रुको_क्रम_ced(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_रुको_क्रम_ced;
	memstick_init_req(&card->current_mrq, MS_TPC_GET_INT, शून्य, 1);
	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);
	वापस card->current_mrq.error;
पूर्ण

अटल पूर्णांक mspro_block_set_पूर्णांकerface(काष्ठा memstick_dev *card,
				     अचिन्हित अक्षर sys_reg)
अणु
	काष्ठा memstick_host *host = card->host;
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	काष्ठा mspro_param_रेजिस्टर param = अणु
		.प्रणाली = sys_reg,
		.data_count = 0,
		.data_address = 0,
		.tpc_param = 0
	पूर्ण;

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_शेष;
	memstick_init_req(&card->current_mrq, MS_TPC_WRITE_REG, &param,
			  माप(param));
	memstick_new_req(host);
	रुको_क्रम_completion(&card->mrq_complete);
	वापस card->current_mrq.error;
पूर्ण

अटल पूर्णांक mspro_block_चयन_पूर्णांकerface(काष्ठा memstick_dev *card)
अणु
	काष्ठा memstick_host *host = card->host;
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	पूर्णांक rc = 0;

try_again:
	अगर (msb->caps & MEMSTICK_CAP_PAR4)
		rc = mspro_block_set_पूर्णांकerface(card, MEMSTICK_SYS_PAR4);
	अन्यथा
		वापस 0;

	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: could not switch to 4-bit mode, error %d\n",
		       dev_name(&card->dev), rc);
		वापस 0;
	पूर्ण

	msb->प्रणाली = MEMSTICK_SYS_PAR4;
	host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_PAR4);
	prपूर्णांकk(KERN_INFO "%s: switching to 4-bit parallel mode\n",
	       dev_name(&card->dev));

	अगर (msb->caps & MEMSTICK_CAP_PAR8) अणु
		rc = mspro_block_set_पूर्णांकerface(card, MEMSTICK_SYS_PAR8);

		अगर (!rc) अणु
			msb->प्रणाली = MEMSTICK_SYS_PAR8;
			host->set_param(host, MEMSTICK_INTERFACE,
					MEMSTICK_PAR8);
			prपूर्णांकk(KERN_INFO
			       "%s: switching to 8-bit parallel mode\n",
			       dev_name(&card->dev));
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING
			       "%s: could not switch to 8-bit mode, error %d\n",
			       dev_name(&card->dev), rc);
	पूर्ण

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_शेष;
	memstick_init_req(&card->current_mrq, MS_TPC_GET_INT, शून्य, 1);
	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);
	rc = card->current_mrq.error;

	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: interface error, trying to fall back to serial\n",
		       dev_name(&card->dev));
		msb->प्रणाली = MEMSTICK_SYS_SERIAL;
		host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);
		msleep(10);
		host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_ON);
		host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_SERIAL);

		rc = memstick_set_rw_addr(card);
		अगर (!rc)
			rc = mspro_block_set_पूर्णांकerface(card, msb->प्रणाली);

		अगर (!rc) अणु
			msleep(150);
			rc = mspro_block_रुको_क्रम_ced(card);
			अगर (rc)
				वापस rc;

			अगर (msb->caps & MEMSTICK_CAP_PAR8) अणु
				msb->caps &= ~MEMSTICK_CAP_PAR8;
				जाओ try_again;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/* Memory allocated क्रम attributes by this function should be मुक्तd by
 * mspro_block_data_clear, no matter अगर the initialization process succeeded
 * or failed.
 */
अटल पूर्णांक mspro_block_पढ़ो_attributes(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	काष्ठा mspro_attribute *attr = शून्य;
	काष्ठा mspro_sys_attr *s_attr = शून्य;
	अचिन्हित अक्षर *buffer = शून्य;
	पूर्णांक cnt, rc, attr_count;
	/* While normally physical device offsets, represented here by
	 * attr_offset and attr_len will be of large numeric types, we can be
	 * sure, that attributes are बंद enough to the beginning of the
	 * device, to save ourselves some trouble.
	 */
	अचिन्हित पूर्णांक addr, attr_offset = 0, attr_len = msb->page_size;

	attr = kदो_स्मृति(msb->page_size, GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	sg_init_one(&msb->req_sg[0], attr, msb->page_size);
	msb->seg_count = 1;
	msb->current_seg = 0;
	msb->current_page = 0;
	msb->data_dir = READ;
	msb->transfer_cmd = MSPRO_CMD_READ_ATRB;

	msb->setup_transfer(card, attr_offset, attr_len);

	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);
	अगर (card->current_mrq.error) अणु
		rc = card->current_mrq.error;
		जाओ out_मुक्त_attr;
	पूर्ण

	अगर (be16_to_cpu(attr->signature) != MSPRO_BLOCK_SIGNATURE) अणु
		prपूर्णांकk(KERN_ERR "%s: unrecognized device signature %x\n",
		       dev_name(&card->dev), be16_to_cpu(attr->signature));
		rc = -ENODEV;
		जाओ out_मुक्त_attr;
	पूर्ण

	अगर (attr->count > MSPRO_BLOCK_MAX_ATTRIBUTES) अणु
		prपूर्णांकk(KERN_WARNING "%s: way too many attribute entries\n",
		       dev_name(&card->dev));
		attr_count = MSPRO_BLOCK_MAX_ATTRIBUTES;
	पूर्ण अन्यथा
		attr_count = attr->count;

	msb->attr_group.attrs = kसुस्मृति(attr_count + 1,
					माप(*msb->attr_group.attrs),
					GFP_KERNEL);
	अगर (!msb->attr_group.attrs) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_attr;
	पूर्ण
	msb->attr_group.name = "media_attributes";

	buffer = kmemdup(attr, attr_len, GFP_KERNEL);
	अगर (!buffer) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_attr;
	पूर्ण

	क्रम (cnt = 0; cnt < attr_count; ++cnt) अणु
		s_attr = kzalloc(माप(काष्ठा mspro_sys_attr), GFP_KERNEL);
		अगर (!s_attr) अणु
			rc = -ENOMEM;
			जाओ out_मुक्त_buffer;
		पूर्ण

		msb->attr_group.attrs[cnt] = &s_attr->dev_attr.attr;
		addr = be32_to_cpu(attr->entries[cnt].address);
		s_attr->size = be32_to_cpu(attr->entries[cnt].size);
		dev_dbg(&card->dev, "adding attribute %d: id %x, address %x, "
			"size %zx\n", cnt, attr->entries[cnt].id, addr,
			s_attr->size);
		s_attr->id = attr->entries[cnt].id;
		अगर (mspro_block_attr_name(s_attr->id))
			snम_लिखो(s_attr->name, माप(s_attr->name), "%s",
				 mspro_block_attr_name(attr->entries[cnt].id));
		अन्यथा
			snम_लिखो(s_attr->name, माप(s_attr->name),
				 "attr_x%02x", attr->entries[cnt].id);

		sysfs_attr_init(&s_attr->dev_attr.attr);
		s_attr->dev_attr.attr.name = s_attr->name;
		s_attr->dev_attr.attr.mode = S_IRUGO;
		s_attr->dev_attr.show = mspro_block_attr_show(s_attr->id);

		अगर (!s_attr->size)
			जारी;

		s_attr->data = kदो_स्मृति(s_attr->size, GFP_KERNEL);
		अगर (!s_attr->data) अणु
			rc = -ENOMEM;
			जाओ out_मुक्त_buffer;
		पूर्ण

		अगर (((addr / msb->page_size) == (attr_offset / msb->page_size))
		    && (((addr + s_attr->size - 1) / msb->page_size)
			== (attr_offset / msb->page_size))) अणु
			स_नकल(s_attr->data, buffer + addr % msb->page_size,
			       s_attr->size);
			जारी;
		पूर्ण

		attr_offset = (addr / msb->page_size) * msb->page_size;

		अगर ((attr_offset + attr_len) < (addr + s_attr->size)) अणु
			kमुक्त(buffer);
			attr_len = (((addr + s_attr->size) / msb->page_size)
				    + 1 ) * msb->page_size - attr_offset;
			buffer = kदो_स्मृति(attr_len, GFP_KERNEL);
			अगर (!buffer) अणु
				rc = -ENOMEM;
				जाओ out_मुक्त_attr;
			पूर्ण
		पूर्ण

		sg_init_one(&msb->req_sg[0], buffer, attr_len);
		msb->seg_count = 1;
		msb->current_seg = 0;
		msb->current_page = 0;
		msb->data_dir = READ;
		msb->transfer_cmd = MSPRO_CMD_READ_ATRB;

		dev_dbg(&card->dev, "reading attribute range %x, %x\n",
			attr_offset, attr_len);

		msb->setup_transfer(card, attr_offset, attr_len);
		memstick_new_req(card->host);
		रुको_क्रम_completion(&card->mrq_complete);
		अगर (card->current_mrq.error) अणु
			rc = card->current_mrq.error;
			जाओ out_मुक्त_buffer;
		पूर्ण

		स_नकल(s_attr->data, buffer + addr % msb->page_size,
		       s_attr->size);
	पूर्ण

	rc = 0;
out_मुक्त_buffer:
	kमुक्त(buffer);
out_मुक्त_attr:
	kमुक्त(attr);
	वापस rc;
पूर्ण

अटल पूर्णांक mspro_block_init_card(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	काष्ठा memstick_host *host = card->host;
	पूर्णांक rc = 0;

	msb->प्रणाली = MEMSTICK_SYS_SERIAL;
	msb->setup_transfer = h_mspro_block_setup_cmd;

	card->reg_addr.r_offset = दुरत्व(काष्ठा mspro_रेजिस्टर, status);
	card->reg_addr.r_length = माप(काष्ठा ms_status_रेजिस्टर);
	card->reg_addr.w_offset = दुरत्व(काष्ठा mspro_रेजिस्टर, param);
	card->reg_addr.w_length = माप(काष्ठा mspro_param_रेजिस्टर);

	अगर (memstick_set_rw_addr(card))
		वापस -EIO;

	msb->caps = host->caps;

	msleep(150);
	rc = mspro_block_रुको_क्रम_ced(card);
	अगर (rc)
		वापस rc;

	rc = mspro_block_चयन_पूर्णांकerface(card);
	अगर (rc)
		वापस rc;

	dev_dbg(&card->dev, "card activated\n");
	अगर (msb->प्रणाली != MEMSTICK_SYS_SERIAL)
		msb->caps |= MEMSTICK_CAP_AUTO_GET_INT;

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_get_ro;
	memstick_init_req(&card->current_mrq, MS_TPC_READ_REG, शून्य,
			  माप(काष्ठा ms_status_रेजिस्टर));
	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);
	अगर (card->current_mrq.error)
		वापस card->current_mrq.error;

	dev_dbg(&card->dev, "card r/w status %d\n", msb->पढ़ो_only ? 0 : 1);

	msb->page_size = 512;
	rc = mspro_block_पढ़ो_attributes(card);
	अगर (rc)
		वापस rc;

	dev_dbg(&card->dev, "attributes loaded\n");
	वापस 0;

पूर्ण

अटल स्थिर काष्ठा blk_mq_ops mspro_mq_ops = अणु
	.queue_rq	= mspro_queue_rq,
पूर्ण;

अटल पूर्णांक mspro_block_init_disk(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	काष्ठा mspro_devinfo *dev_info = शून्य;
	काष्ठा mspro_sys_info *sys_info = शून्य;
	काष्ठा mspro_sys_attr *s_attr = शून्य;
	पूर्णांक rc, disk_id;
	अचिन्हित दीर्घ capacity;

	क्रम (rc = 0; msb->attr_group.attrs[rc]; ++rc) अणु
		s_attr = mspro_from_sysfs_attr(msb->attr_group.attrs[rc]);

		अगर (s_attr->id == MSPRO_BLOCK_ID_DEVINFO)
			dev_info = s_attr->data;
		अन्यथा अगर (s_attr->id == MSPRO_BLOCK_ID_SYSINFO)
			sys_info = s_attr->data;
	पूर्ण

	अगर (!dev_info || !sys_info)
		वापस -ENODEV;

	msb->cylinders = be16_to_cpu(dev_info->cylinders);
	msb->heads = be16_to_cpu(dev_info->heads);
	msb->sectors_per_track = be16_to_cpu(dev_info->sectors_per_track);

	msb->page_size = be16_to_cpu(sys_info->unit_size);

	mutex_lock(&mspro_block_disk_lock);
	disk_id = idr_alloc(&mspro_block_disk_idr, card, 0, 256, GFP_KERNEL);
	mutex_unlock(&mspro_block_disk_lock);
	अगर (disk_id < 0)
		वापस disk_id;

	msb->disk = alloc_disk(1 << MSPRO_BLOCK_PART_SHIFT);
	अगर (!msb->disk) अणु
		rc = -ENOMEM;
		जाओ out_release_id;
	पूर्ण

	msb->queue = blk_mq_init_sq_queue(&msb->tag_set, &mspro_mq_ops, 2,
						BLK_MQ_F_SHOULD_MERGE);
	अगर (IS_ERR(msb->queue)) अणु
		rc = PTR_ERR(msb->queue);
		msb->queue = शून्य;
		जाओ out_put_disk;
	पूर्ण

	msb->queue->queuedata = card;

	blk_queue_max_hw_sectors(msb->queue, MSPRO_BLOCK_MAX_PAGES);
	blk_queue_max_segments(msb->queue, MSPRO_BLOCK_MAX_SEGS);
	blk_queue_max_segment_size(msb->queue,
				   MSPRO_BLOCK_MAX_PAGES * msb->page_size);

	msb->disk->major = major;
	msb->disk->first_minor = disk_id << MSPRO_BLOCK_PART_SHIFT;
	msb->disk->fops = &ms_block_bकरोps;
	msb->usage_count = 1;
	msb->disk->निजी_data = msb;
	msb->disk->queue = msb->queue;

	प्र_लिखो(msb->disk->disk_name, "mspblk%d", disk_id);

	blk_queue_logical_block_size(msb->queue, msb->page_size);

	capacity = be16_to_cpu(sys_info->user_block_count);
	capacity *= be16_to_cpu(sys_info->block_size);
	capacity *= msb->page_size >> 9;
	set_capacity(msb->disk, capacity);
	dev_dbg(&card->dev, "capacity set %ld\n", capacity);

	device_add_disk(&card->dev, msb->disk, शून्य);
	msb->active = 1;
	वापस 0;

out_put_disk:
	put_disk(msb->disk);
out_release_id:
	mutex_lock(&mspro_block_disk_lock);
	idr_हटाओ(&mspro_block_disk_idr, disk_id);
	mutex_unlock(&mspro_block_disk_lock);
	वापस rc;
पूर्ण

अटल व्योम mspro_block_data_clear(काष्ठा mspro_block_data *msb)
अणु
	पूर्णांक cnt;
	काष्ठा mspro_sys_attr *s_attr;

	अगर (msb->attr_group.attrs) अणु
		क्रम (cnt = 0; msb->attr_group.attrs[cnt]; ++cnt) अणु
			s_attr = mspro_from_sysfs_attr(msb->attr_group
							   .attrs[cnt]);
			kमुक्त(s_attr->data);
			kमुक्त(s_attr);
		पूर्ण
		kमुक्त(msb->attr_group.attrs);
	पूर्ण

	msb->card = शून्य;
पूर्ण

अटल पूर्णांक mspro_block_check_card(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);

	वापस (msb->active == 1);
पूर्ण

अटल पूर्णांक mspro_block_probe(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb;
	पूर्णांक rc = 0;

	msb = kzalloc(माप(काष्ठा mspro_block_data), GFP_KERNEL);
	अगर (!msb)
		वापस -ENOMEM;
	memstick_set_drvdata(card, msb);
	msb->card = card;
	spin_lock_init(&msb->q_lock);

	rc = mspro_block_init_card(card);

	अगर (rc)
		जाओ out_मुक्त;

	rc = sysfs_create_group(&card->dev.kobj, &msb->attr_group);
	अगर (rc)
		जाओ out_मुक्त;

	rc = mspro_block_init_disk(card);
	अगर (!rc) अणु
		card->check = mspro_block_check_card;
		card->stop = mspro_block_stop;
		card->start = mspro_block_start;
		वापस 0;
	पूर्ण

	sysfs_हटाओ_group(&card->dev.kobj, &msb->attr_group);
out_मुक्त:
	memstick_set_drvdata(card, शून्य);
	mspro_block_data_clear(msb);
	kमुक्त(msb);
	वापस rc;
पूर्ण

अटल व्योम mspro_block_हटाओ(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msb->q_lock, flags);
	msb->eject = 1;
	spin_unlock_irqrestore(&msb->q_lock, flags);
	blk_mq_start_hw_queues(msb->queue);

	del_gendisk(msb->disk);
	dev_dbg(&card->dev, "mspro block remove\n");

	blk_cleanup_queue(msb->queue);
	blk_mq_मुक्त_tag_set(&msb->tag_set);
	msb->queue = शून्य;

	sysfs_हटाओ_group(&card->dev.kobj, &msb->attr_group);

	mutex_lock(&mspro_block_disk_lock);
	mspro_block_data_clear(msb);
	mutex_unlock(&mspro_block_disk_lock);

	mspro_block_disk_release(msb->disk);
	memstick_set_drvdata(card, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक mspro_block_suspend(काष्ठा memstick_dev *card, pm_message_t state)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	अचिन्हित दीर्घ flags;

	blk_mq_stop_hw_queues(msb->queue);

	spin_lock_irqsave(&msb->q_lock, flags);
	msb->active = 0;
	spin_unlock_irqrestore(&msb->q_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mspro_block_resume(काष्ठा memstick_dev *card)
अणु
	काष्ठा mspro_block_data *msb = memstick_get_drvdata(card);
	पूर्णांक rc = 0;

#अगर_घोषित CONFIG_MEMSTICK_UNSAFE_RESUME

	काष्ठा mspro_block_data *new_msb;
	काष्ठा memstick_host *host = card->host;
	काष्ठा mspro_sys_attr *s_attr, *r_attr;
	अचिन्हित अक्षर cnt;

	mutex_lock(&host->lock);
	new_msb = kzalloc(माप(काष्ठा mspro_block_data), GFP_KERNEL);
	अगर (!new_msb) अणु
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	new_msb->card = card;
	memstick_set_drvdata(card, new_msb);
	rc = mspro_block_init_card(card);
	अगर (rc)
		जाओ out_मुक्त;

	क्रम (cnt = 0; new_msb->attr_group.attrs[cnt]
		      && msb->attr_group.attrs[cnt]; ++cnt) अणु
		s_attr = mspro_from_sysfs_attr(new_msb->attr_group.attrs[cnt]);
		r_attr = mspro_from_sysfs_attr(msb->attr_group.attrs[cnt]);

		अगर (s_attr->id == MSPRO_BLOCK_ID_SYSINFO
		    && r_attr->id == s_attr->id) अणु
			अगर (स_भेद(s_attr->data, r_attr->data, s_attr->size))
				अवरोध;

			msb->active = 1;
			अवरोध;
		पूर्ण
	पूर्ण

out_मुक्त:
	memstick_set_drvdata(card, msb);
	mspro_block_data_clear(new_msb);
	kमुक्त(new_msb);
out_unlock:
	mutex_unlock(&host->lock);

#पूर्ण_अगर /* CONFIG_MEMSTICK_UNSAFE_RESUME */

	blk_mq_start_hw_queues(msb->queue);
	वापस rc;
पूर्ण

#अन्यथा

#घोषणा mspro_block_suspend शून्य
#घोषणा mspro_block_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा memstick_device_id mspro_block_id_tbl[] = अणु
	अणुMEMSTICK_MATCH_ALL, MEMSTICK_TYPE_PRO, MEMSTICK_CATEGORY_STORAGE_DUO,
	 MEMSTICK_CLASS_DUOपूर्ण,
	अणुपूर्ण
पूर्ण;


अटल काष्ठा memstick_driver mspro_block_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
		.owner = THIS_MODULE
	पूर्ण,
	.id_table = mspro_block_id_tbl,
	.probe    = mspro_block_probe,
	.हटाओ   = mspro_block_हटाओ,
	.suspend  = mspro_block_suspend,
	.resume   = mspro_block_resume
पूर्ण;

अटल पूर्णांक __init mspro_block_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;

	rc = रेजिस्टर_blkdev(major, DRIVER_NAME);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": failed to register "
		       "major %d, error %d\n", major, rc);
		वापस rc;
	पूर्ण
	अगर (!major)
		major = rc;

	rc = memstick_रेजिस्टर_driver(&mspro_block_driver);
	अगर (rc)
		unरेजिस्टर_blkdev(major, DRIVER_NAME);
	वापस rc;
पूर्ण

अटल व्योम __निकास mspro_block_निकास(व्योम)
अणु
	memstick_unरेजिस्टर_driver(&mspro_block_driver);
	unरेजिस्टर_blkdev(major, DRIVER_NAME);
	idr_destroy(&mspro_block_disk_idr);
पूर्ण

module_init(mspro_block_init);
module_निकास(mspro_block_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("Sony MemoryStickPro block device driver");
MODULE_DEVICE_TABLE(memstick, mspro_block_id_tbl);
