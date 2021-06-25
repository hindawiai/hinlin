<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/dmi.h>
#समावेश <यंत्र/unaligned.h>

#अगर_अघोषित SMBIOS_ENTRY_POINT_SCAN_START
#घोषणा SMBIOS_ENTRY_POINT_SCAN_START 0xF0000
#पूर्ण_अगर

काष्ठा kobject *dmi_kobj;
EXPORT_SYMBOL_GPL(dmi_kobj);

/*
 * DMI stands क्रम "Desktop Management Interface".  It is part
 * of and an antecedent to, SMBIOS, which stands क्रम System
 * Management BIOS.  See further: https://www.dmtf.org/standards
 */
अटल स्थिर अक्षर dmi_empty_string[] = "";

अटल u32 dmi_ver __initdata;
अटल u32 dmi_len;
अटल u16 dmi_num;
अटल u8 smbios_entry_poपूर्णांक[32];
अटल पूर्णांक smbios_entry_poपूर्णांक_size;

/* DMI प्रणाली identअगरication string used during boot */
अटल अक्षर dmi_ids_string[128] __initdata;

अटल काष्ठा dmi_memdev_info अणु
	स्थिर अक्षर *device;
	स्थिर अक्षर *bank;
	u64 size;		/* bytes */
	u16 handle;
	u8 type;		/* DDR2, DDR3, DDR4 etc */
पूर्ण *dmi_memdev;
अटल पूर्णांक dmi_memdev_nr;

अटल स्थिर अक्षर * __init dmi_string_nosave(स्थिर काष्ठा dmi_header *dm, u8 s)
अणु
	स्थिर u8 *bp = ((u8 *) dm) + dm->length;
	स्थिर u8 *nsp;

	अगर (s) अणु
		जबतक (--s > 0 && *bp)
			bp += म_माप(bp) + 1;

		/* Strings containing only spaces are considered empty */
		nsp = bp;
		जबतक (*nsp == ' ')
			nsp++;
		अगर (*nsp != '\0')
			वापस bp;
	पूर्ण

	वापस dmi_empty_string;
पूर्ण

अटल स्थिर अक्षर * __init dmi_string(स्थिर काष्ठा dmi_header *dm, u8 s)
अणु
	स्थिर अक्षर *bp = dmi_string_nosave(dm, s);
	अक्षर *str;
	माप_प्रकार len;

	अगर (bp == dmi_empty_string)
		वापस dmi_empty_string;

	len = म_माप(bp) + 1;
	str = dmi_alloc(len);
	अगर (str != शून्य)
		म_नकल(str, bp);

	वापस str;
पूर्ण

/*
 *	We have to be cautious here. We have seen BIOSes with DMI poपूर्णांकers
 *	poपूर्णांकing to completely the wrong place क्रम example
 */
अटल व्योम dmi_decode_table(u8 *buf,
			     व्योम (*decode)(स्थिर काष्ठा dmi_header *, व्योम *),
			     व्योम *निजी_data)
अणु
	u8 *data = buf;
	पूर्णांक i = 0;

	/*
	 * Stop when we have seen all the items the table claimed to have
	 * (SMBIOS < 3.0 only) OR we reach an end-of-table marker (SMBIOS
	 * >= 3.0 only) OR we run off the end of the table (should never
	 * happen but someबार करोes on bogus implementations.)
	 */
	जबतक ((!dmi_num || i < dmi_num) &&
	       (data - buf + माप(काष्ठा dmi_header)) <= dmi_len) अणु
		स्थिर काष्ठा dmi_header *dm = (स्थिर काष्ठा dmi_header *)data;

		/*
		 *  We want to know the total length (क्रमmatted area and
		 *  strings) beक्रमe decoding to make sure we won't run off the
		 *  table in dmi_decode or dmi_string
		 */
		data += dm->length;
		जबतक ((data - buf < dmi_len - 1) && (data[0] || data[1]))
			data++;
		अगर (data - buf < dmi_len - 1)
			decode(dm, निजी_data);

		data += 2;
		i++;

		/*
		 * 7.45 End-of-Table (Type 127) [SMBIOS reference spec v3.0.0]
		 * For tables behind a 64-bit entry poपूर्णांक, we have no item
		 * count and no exact table length, so stop on end-of-table
		 * marker. For tables behind a 32-bit entry poपूर्णांक, we have
		 * seen OEM काष्ठाures behind the end-of-table marker on
		 * some प्रणालीs, so करोn't trust it.
		 */
		अगर (!dmi_num && dm->type == DMI_ENTRY_END_OF_TABLE)
			अवरोध;
	पूर्ण

	/* Trim DMI table length अगर needed */
	अगर (dmi_len > data - buf)
		dmi_len = data - buf;
पूर्ण

अटल phys_addr_t dmi_base;

अटल पूर्णांक __init dmi_walk_early(व्योम (*decode)(स्थिर काष्ठा dmi_header *,
		व्योम *))
अणु
	u8 *buf;
	u32 orig_dmi_len = dmi_len;

	buf = dmi_early_remap(dmi_base, orig_dmi_len);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	dmi_decode_table(buf, decode, शून्य);

	add_device_अक्रमomness(buf, dmi_len);

	dmi_early_unmap(buf, orig_dmi_len);
	वापस 0;
पूर्ण

अटल पूर्णांक __init dmi_checksum(स्थिर u8 *buf, u8 len)
अणु
	u8 sum = 0;
	पूर्णांक a;

	क्रम (a = 0; a < len; a++)
		sum += buf[a];

	वापस sum == 0;
पूर्ण

अटल स्थिर अक्षर *dmi_ident[DMI_STRING_MAX];
अटल LIST_HEAD(dmi_devices);
पूर्णांक dmi_available;
EXPORT_SYMBOL_GPL(dmi_available);

/*
 *	Save a DMI string
 */
अटल व्योम __init dmi_save_ident(स्थिर काष्ठा dmi_header *dm, पूर्णांक slot,
		पूर्णांक string)
अणु
	स्थिर अक्षर *d = (स्थिर अक्षर *) dm;
	स्थिर अक्षर *p;

	अगर (dmi_ident[slot] || dm->length <= string)
		वापस;

	p = dmi_string(dm, d[string]);
	अगर (p == शून्य)
		वापस;

	dmi_ident[slot] = p;
पूर्ण

अटल व्योम __init dmi_save_release(स्थिर काष्ठा dmi_header *dm, पूर्णांक slot,
		पूर्णांक index)
अणु
	स्थिर u8 *minor, *major;
	अक्षर *s;

	/* If the table करोesn't have the field, let's वापस */
	अगर (dmi_ident[slot] || dm->length < index)
		वापस;

	minor = (u8 *) dm + index;
	major = (u8 *) dm + index - 1;

	/* As per the spec, अगर the प्रणाली करोesn't support this field,
	 * the value is FF
	 */
	अगर (*major == 0xFF && *minor == 0xFF)
		वापस;

	s = dmi_alloc(8);
	अगर (!s)
		वापस;

	प्र_लिखो(s, "%u.%u", *major, *minor);

	dmi_ident[slot] = s;
पूर्ण

अटल व्योम __init dmi_save_uuid(स्थिर काष्ठा dmi_header *dm, पूर्णांक slot,
		पूर्णांक index)
अणु
	स्थिर u8 *d;
	अक्षर *s;
	पूर्णांक is_ff = 1, is_00 = 1, i;

	अगर (dmi_ident[slot] || dm->length < index + 16)
		वापस;

	d = (u8 *) dm + index;
	क्रम (i = 0; i < 16 && (is_ff || is_00); i++) अणु
		अगर (d[i] != 0x00)
			is_00 = 0;
		अगर (d[i] != 0xFF)
			is_ff = 0;
	पूर्ण

	अगर (is_ff || is_00)
		वापस;

	s = dmi_alloc(16*2+4+1);
	अगर (!s)
		वापस;

	/*
	 * As of version 2.6 of the SMBIOS specअगरication, the first 3 fields of
	 * the UUID are supposed to be little-endian encoded.  The specअगरication
	 * says that this is the defacto standard.
	 */
	अगर (dmi_ver >= 0x020600)
		प्र_लिखो(s, "%pUl", d);
	अन्यथा
		प्र_लिखो(s, "%pUb", d);

	dmi_ident[slot] = s;
पूर्ण

अटल व्योम __init dmi_save_type(स्थिर काष्ठा dmi_header *dm, पूर्णांक slot,
		पूर्णांक index)
अणु
	स्थिर u8 *d;
	अक्षर *s;

	अगर (dmi_ident[slot] || dm->length <= index)
		वापस;

	s = dmi_alloc(4);
	अगर (!s)
		वापस;

	d = (u8 *) dm + index;
	प्र_लिखो(s, "%u", *d & 0x7F);
	dmi_ident[slot] = s;
पूर्ण

अटल व्योम __init dmi_save_one_device(पूर्णांक type, स्थिर अक्षर *name)
अणु
	काष्ठा dmi_device *dev;

	/* No duplicate device */
	अगर (dmi_find_device(type, name, शून्य))
		वापस;

	dev = dmi_alloc(माप(*dev) + म_माप(name) + 1);
	अगर (!dev)
		वापस;

	dev->type = type;
	म_नकल((अक्षर *)(dev + 1), name);
	dev->name = (अक्षर *)(dev + 1);
	dev->device_data = शून्य;
	list_add(&dev->list, &dmi_devices);
पूर्ण

अटल व्योम __init dmi_save_devices(स्थिर काष्ठा dmi_header *dm)
अणु
	पूर्णांक i, count = (dm->length - माप(काष्ठा dmi_header)) / 2;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर अक्षर *d = (अक्षर *)(dm + 1) + (i * 2);

		/* Skip disabled device */
		अगर ((*d & 0x80) == 0)
			जारी;

		dmi_save_one_device(*d & 0x7f, dmi_string_nosave(dm, *(d + 1)));
	पूर्ण
पूर्ण

अटल व्योम __init dmi_save_oem_strings_devices(स्थिर काष्ठा dmi_header *dm)
अणु
	पूर्णांक i, count;
	काष्ठा dmi_device *dev;

	अगर (dm->length < 0x05)
		वापस;

	count = *(u8 *)(dm + 1);
	क्रम (i = 1; i <= count; i++) अणु
		स्थिर अक्षर *devname = dmi_string(dm, i);

		अगर (devname == dmi_empty_string)
			जारी;

		dev = dmi_alloc(माप(*dev));
		अगर (!dev)
			अवरोध;

		dev->type = DMI_DEV_TYPE_OEM_STRING;
		dev->name = devname;
		dev->device_data = शून्य;

		list_add(&dev->list, &dmi_devices);
	पूर्ण
पूर्ण

अटल व्योम __init dmi_save_ipmi_device(स्थिर काष्ठा dmi_header *dm)
अणु
	काष्ठा dmi_device *dev;
	व्योम *data;

	data = dmi_alloc(dm->length);
	अगर (data == शून्य)
		वापस;

	स_नकल(data, dm, dm->length);

	dev = dmi_alloc(माप(*dev));
	अगर (!dev)
		वापस;

	dev->type = DMI_DEV_TYPE_IPMI;
	dev->name = "IPMI controller";
	dev->device_data = data;

	list_add_tail(&dev->list, &dmi_devices);
पूर्ण

अटल व्योम __init dmi_save_dev_pciaddr(पूर्णांक instance, पूर्णांक segment, पूर्णांक bus,
					पूर्णांक devfn, स्थिर अक्षर *name, पूर्णांक type)
अणु
	काष्ठा dmi_dev_onboard *dev;

	/* Ignore invalid values */
	अगर (type == DMI_DEV_TYPE_DEV_SLOT &&
	    segment == 0xFFFF && bus == 0xFF && devfn == 0xFF)
		वापस;

	dev = dmi_alloc(माप(*dev) + म_माप(name) + 1);
	अगर (!dev)
		वापस;

	dev->instance = instance;
	dev->segment = segment;
	dev->bus = bus;
	dev->devfn = devfn;

	म_नकल((अक्षर *)&dev[1], name);
	dev->dev.type = type;
	dev->dev.name = (अक्षर *)&dev[1];
	dev->dev.device_data = dev;

	list_add(&dev->dev.list, &dmi_devices);
पूर्ण

अटल व्योम __init dmi_save_extended_devices(स्थिर काष्ठा dmi_header *dm)
अणु
	स्थिर अक्षर *name;
	स्थिर u8 *d = (u8 *)dm;

	अगर (dm->length < 0x0B)
		वापस;

	/* Skip disabled device */
	अगर ((d[0x5] & 0x80) == 0)
		वापस;

	name = dmi_string_nosave(dm, d[0x4]);
	dmi_save_dev_pciaddr(d[0x6], *(u16 *)(d + 0x7), d[0x9], d[0xA], name,
			     DMI_DEV_TYPE_DEV_ONBOARD);
	dmi_save_one_device(d[0x5] & 0x7f, name);
पूर्ण

अटल व्योम __init dmi_save_प्रणाली_slot(स्थिर काष्ठा dmi_header *dm)
अणु
	स्थिर u8 *d = (u8 *)dm;

	/* Need SMBIOS 2.6+ काष्ठाure */
	अगर (dm->length < 0x11)
		वापस;
	dmi_save_dev_pciaddr(*(u16 *)(d + 0x9), *(u16 *)(d + 0xD), d[0xF],
			     d[0x10], dmi_string_nosave(dm, d[0x4]),
			     DMI_DEV_TYPE_DEV_SLOT);
पूर्ण

अटल व्योम __init count_mem_devices(स्थिर काष्ठा dmi_header *dm, व्योम *v)
अणु
	अगर (dm->type != DMI_ENTRY_MEM_DEVICE)
		वापस;
	dmi_memdev_nr++;
पूर्ण

अटल व्योम __init save_mem_devices(स्थिर काष्ठा dmi_header *dm, व्योम *v)
अणु
	स्थिर अक्षर *d = (स्थिर अक्षर *)dm;
	अटल पूर्णांक nr;
	u64 bytes;
	u16 size;

	अगर (dm->type != DMI_ENTRY_MEM_DEVICE || dm->length < 0x13)
		वापस;
	अगर (nr >= dmi_memdev_nr) अणु
		pr_warn(FW_BUG "Too many DIMM entries in SMBIOS table\n");
		वापस;
	पूर्ण
	dmi_memdev[nr].handle = get_unaligned(&dm->handle);
	dmi_memdev[nr].device = dmi_string(dm, d[0x10]);
	dmi_memdev[nr].bank = dmi_string(dm, d[0x11]);
	dmi_memdev[nr].type = d[0x12];

	size = get_unaligned((u16 *)&d[0xC]);
	अगर (size == 0)
		bytes = 0;
	अन्यथा अगर (size == 0xffff)
		bytes = ~0ull;
	अन्यथा अगर (size & 0x8000)
		bytes = (u64)(size & 0x7fff) << 10;
	अन्यथा अगर (size != 0x7fff || dm->length < 0x20)
		bytes = (u64)size << 20;
	अन्यथा
		bytes = (u64)get_unaligned((u32 *)&d[0x1C]) << 20;

	dmi_memdev[nr].size = bytes;
	nr++;
पूर्ण

अटल व्योम __init dmi_memdev_walk(व्योम)
अणु
	अगर (dmi_walk_early(count_mem_devices) == 0 && dmi_memdev_nr) अणु
		dmi_memdev = dmi_alloc(माप(*dmi_memdev) * dmi_memdev_nr);
		अगर (dmi_memdev)
			dmi_walk_early(save_mem_devices);
	पूर्ण
पूर्ण

/*
 *	Process a DMI table entry. Right now all we care about are the BIOS
 *	and machine entries. For 2.5 we should pull the smbus controller info
 *	out of here.
 */
अटल व्योम __init dmi_decode(स्थिर काष्ठा dmi_header *dm, व्योम *dummy)
अणु
	चयन (dm->type) अणु
	हाल 0:		/* BIOS Inक्रमmation */
		dmi_save_ident(dm, DMI_BIOS_VENDOR, 4);
		dmi_save_ident(dm, DMI_BIOS_VERSION, 5);
		dmi_save_ident(dm, DMI_BIOS_DATE, 8);
		dmi_save_release(dm, DMI_BIOS_RELEASE, 21);
		dmi_save_release(dm, DMI_EC_FIRMWARE_RELEASE, 23);
		अवरोध;
	हाल 1:		/* System Inक्रमmation */
		dmi_save_ident(dm, DMI_SYS_VENDOR, 4);
		dmi_save_ident(dm, DMI_PRODUCT_NAME, 5);
		dmi_save_ident(dm, DMI_PRODUCT_VERSION, 6);
		dmi_save_ident(dm, DMI_PRODUCT_SERIAL, 7);
		dmi_save_uuid(dm, DMI_PRODUCT_UUID, 8);
		dmi_save_ident(dm, DMI_PRODUCT_SKU, 25);
		dmi_save_ident(dm, DMI_PRODUCT_FAMILY, 26);
		अवरोध;
	हाल 2:		/* Base Board Inक्रमmation */
		dmi_save_ident(dm, DMI_BOARD_VENDOR, 4);
		dmi_save_ident(dm, DMI_BOARD_NAME, 5);
		dmi_save_ident(dm, DMI_BOARD_VERSION, 6);
		dmi_save_ident(dm, DMI_BOARD_SERIAL, 7);
		dmi_save_ident(dm, DMI_BOARD_ASSET_TAG, 8);
		अवरोध;
	हाल 3:		/* Chassis Inक्रमmation */
		dmi_save_ident(dm, DMI_CHASSIS_VENDOR, 4);
		dmi_save_type(dm, DMI_CHASSIS_TYPE, 5);
		dmi_save_ident(dm, DMI_CHASSIS_VERSION, 6);
		dmi_save_ident(dm, DMI_CHASSIS_SERIAL, 7);
		dmi_save_ident(dm, DMI_CHASSIS_ASSET_TAG, 8);
		अवरोध;
	हाल 9:		/* System Slots */
		dmi_save_प्रणाली_slot(dm);
		अवरोध;
	हाल 10:	/* Onboard Devices Inक्रमmation */
		dmi_save_devices(dm);
		अवरोध;
	हाल 11:	/* OEM Strings */
		dmi_save_oem_strings_devices(dm);
		अवरोध;
	हाल 38:	/* IPMI Device Inक्रमmation */
		dmi_save_ipmi_device(dm);
		अवरोध;
	हाल 41:	/* Onboard Devices Extended Inक्रमmation */
		dmi_save_extended_devices(dm);
	पूर्ण
पूर्ण

अटल पूर्णांक __init prपूर्णांक_filtered(अक्षर *buf, माप_प्रकार len, स्थिर अक्षर *info)
अणु
	पूर्णांक c = 0;
	स्थिर अक्षर *p;

	अगर (!info)
		वापस c;

	क्रम (p = info; *p; p++)
		अगर (है_छाप(*p))
			c += scnम_लिखो(buf + c, len - c, "%c", *p);
		अन्यथा
			c += scnम_लिखो(buf + c, len - c, "\\x%02x", *p & 0xff);
	वापस c;
पूर्ण

अटल व्योम __init dmi_क्रमmat_ids(अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक c = 0;
	स्थिर अक्षर *board;	/* Board Name is optional */

	c += prपूर्णांक_filtered(buf + c, len - c,
			    dmi_get_प्रणाली_info(DMI_SYS_VENDOR));
	c += scnम_लिखो(buf + c, len - c, " ");
	c += prपूर्णांक_filtered(buf + c, len - c,
			    dmi_get_प्रणाली_info(DMI_PRODUCT_NAME));

	board = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
	अगर (board) अणु
		c += scnम_लिखो(buf + c, len - c, "/");
		c += prपूर्णांक_filtered(buf + c, len - c, board);
	पूर्ण
	c += scnम_लिखो(buf + c, len - c, ", BIOS ");
	c += prपूर्णांक_filtered(buf + c, len - c,
			    dmi_get_प्रणाली_info(DMI_BIOS_VERSION));
	c += scnम_लिखो(buf + c, len - c, " ");
	c += prपूर्णांक_filtered(buf + c, len - c,
			    dmi_get_प्रणाली_info(DMI_BIOS_DATE));
पूर्ण

/*
 * Check क्रम DMI/SMBIOS headers in the प्रणाली firmware image.  Any
 * SMBIOS header must start 16 bytes beक्रमe the DMI header, so take a
 * 32 byte buffer and check क्रम DMI at offset 16 and SMBIOS at offset
 * 0.  If the DMI header is present, set dmi_ver accordingly (SMBIOS
 * takes precedence) and वापस 0.  Otherwise वापस 1.
 */
अटल पूर्णांक __init dmi_present(स्थिर u8 *buf)
अणु
	u32 smbios_ver;

	अगर (स_भेद(buf, "_SM_", 4) == 0 &&
	    buf[5] < 32 && dmi_checksum(buf, buf[5])) अणु
		smbios_ver = get_unaligned_be16(buf + 6);
		smbios_entry_poपूर्णांक_size = buf[5];
		स_नकल(smbios_entry_poपूर्णांक, buf, smbios_entry_poपूर्णांक_size);

		/* Some BIOS report weird SMBIOS version, fix that up */
		चयन (smbios_ver) अणु
		हाल 0x021F:
		हाल 0x0221:
			pr_debug("SMBIOS version fixup (2.%d->2.%d)\n",
				 smbios_ver & 0xFF, 3);
			smbios_ver = 0x0203;
			अवरोध;
		हाल 0x0233:
			pr_debug("SMBIOS version fixup (2.%d->2.%d)\n", 51, 6);
			smbios_ver = 0x0206;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		smbios_ver = 0;
	पूर्ण

	buf += 16;

	अगर (स_भेद(buf, "_DMI_", 5) == 0 && dmi_checksum(buf, 15)) अणु
		अगर (smbios_ver)
			dmi_ver = smbios_ver;
		अन्यथा
			dmi_ver = (buf[14] & 0xF0) << 4 | (buf[14] & 0x0F);
		dmi_ver <<= 8;
		dmi_num = get_unaligned_le16(buf + 12);
		dmi_len = get_unaligned_le16(buf + 6);
		dmi_base = get_unaligned_le32(buf + 8);

		अगर (dmi_walk_early(dmi_decode) == 0) अणु
			अगर (smbios_ver) अणु
				pr_info("SMBIOS %d.%d present.\n",
					dmi_ver >> 16, (dmi_ver >> 8) & 0xFF);
			पूर्ण अन्यथा अणु
				smbios_entry_poपूर्णांक_size = 15;
				स_नकल(smbios_entry_poपूर्णांक, buf,
				       smbios_entry_poपूर्णांक_size);
				pr_info("Legacy DMI %d.%d present.\n",
					dmi_ver >> 16, (dmi_ver >> 8) & 0xFF);
			पूर्ण
			dmi_क्रमmat_ids(dmi_ids_string, माप(dmi_ids_string));
			pr_info("DMI: %s\n", dmi_ids_string);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Check क्रम the SMBIOS 3.0 64-bit entry poपूर्णांक signature. Unlike the legacy
 * 32-bit entry poपूर्णांक, there is no embedded DMI header (_DMI_) in here.
 */
अटल पूर्णांक __init dmi_smbios3_present(स्थिर u8 *buf)
अणु
	अगर (स_भेद(buf, "_SM3_", 5) == 0 &&
	    buf[6] < 32 && dmi_checksum(buf, buf[6])) अणु
		dmi_ver = get_unaligned_be32(buf + 6) & 0xFFFFFF;
		dmi_num = 0;			/* No दीर्घer specअगरied */
		dmi_len = get_unaligned_le32(buf + 12);
		dmi_base = get_unaligned_le64(buf + 16);
		smbios_entry_poपूर्णांक_size = buf[6];
		स_नकल(smbios_entry_poपूर्णांक, buf, smbios_entry_poपूर्णांक_size);

		अगर (dmi_walk_early(dmi_decode) == 0) अणु
			pr_info("SMBIOS %d.%d.%d present.\n",
				dmi_ver >> 16, (dmi_ver >> 8) & 0xFF,
				dmi_ver & 0xFF);
			dmi_क्रमmat_ids(dmi_ids_string, माप(dmi_ids_string));
			pr_info("DMI: %s\n", dmi_ids_string);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम __init dmi_scan_machine(व्योम)
अणु
	अक्षर __iomem *p, *q;
	अक्षर buf[32];

	अगर (efi_enabled(EFI_CONFIG_TABLES)) अणु
		/*
		 * According to the DMTF SMBIOS reference spec v3.0.0, it is
		 * allowed to define both the 64-bit entry poपूर्णांक (smbios3) and
		 * the 32-bit entry poपूर्णांक (smbios), in which हाल they should
		 * either both poपूर्णांक to the same SMBIOS काष्ठाure table, or the
		 * table poपूर्णांकed to by the 64-bit entry poपूर्णांक should contain a
		 * superset of the table contents poपूर्णांकed to by the 32-bit entry
		 * poपूर्णांक (section 5.2)
		 * This implies that the 64-bit entry poपूर्णांक should have
		 * precedence अगर it is defined and supported by the OS. If we
		 * have the 64-bit entry poपूर्णांक, but fail to decode it, fall
		 * back to the legacy one (अगर available)
		 */
		अगर (efi.smbios3 != EFI_INVALID_TABLE_ADDR) अणु
			p = dmi_early_remap(efi.smbios3, 32);
			अगर (p == शून्य)
				जाओ error;
			स_नकल_fromio(buf, p, 32);
			dmi_early_unmap(p, 32);

			अगर (!dmi_smbios3_present(buf)) अणु
				dmi_available = 1;
				वापस;
			पूर्ण
		पूर्ण
		अगर (efi.smbios == EFI_INVALID_TABLE_ADDR)
			जाओ error;

		/* This is called as a core_initcall() because it isn't
		 * needed during early boot.  This also means we can
		 * iounmap the space when we're करोne with it.
		 */
		p = dmi_early_remap(efi.smbios, 32);
		अगर (p == शून्य)
			जाओ error;
		स_नकल_fromio(buf, p, 32);
		dmi_early_unmap(p, 32);

		अगर (!dmi_present(buf)) अणु
			dmi_available = 1;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_DMI_SCAN_MACHINE_NON_EFI_FALLBACK)) अणु
		p = dmi_early_remap(SMBIOS_ENTRY_POINT_SCAN_START, 0x10000);
		अगर (p == शून्य)
			जाओ error;

		/*
		 * Same logic as above, look क्रम a 64-bit entry poपूर्णांक
		 * first, and अगर not found, fall back to 32-bit entry poपूर्णांक.
		 */
		स_नकल_fromio(buf, p, 16);
		क्रम (q = p + 16; q < p + 0x10000; q += 16) अणु
			स_नकल_fromio(buf + 16, q, 16);
			अगर (!dmi_smbios3_present(buf)) अणु
				dmi_available = 1;
				dmi_early_unmap(p, 0x10000);
				वापस;
			पूर्ण
			स_नकल(buf, buf + 16, 16);
		पूर्ण

		/*
		 * Iterate over all possible DMI header addresses q.
		 * Maपूर्णांकain the 32 bytes around q in buf.  On the
		 * first iteration, substitute zero क्रम the
		 * out-of-range bytes so there is no chance of falsely
		 * detecting an SMBIOS header.
		 */
		स_रखो(buf, 0, 16);
		क्रम (q = p; q < p + 0x10000; q += 16) अणु
			स_नकल_fromio(buf + 16, q, 16);
			अगर (!dmi_present(buf)) अणु
				dmi_available = 1;
				dmi_early_unmap(p, 0x10000);
				वापस;
			पूर्ण
			स_नकल(buf, buf + 16, 16);
		पूर्ण
		dmi_early_unmap(p, 0x10000);
	पूर्ण
 error:
	pr_info("DMI not present or invalid.\n");
पूर्ण

अटल sमाप_प्रकार raw_table_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *attr, अक्षर *buf,
			      loff_t pos, माप_प्रकार count)
अणु
	स_नकल(buf, attr->निजी + pos, count);
	वापस count;
पूर्ण

अटल BIN_ATTR(smbios_entry_poपूर्णांक, S_IRUSR, raw_table_पढ़ो, शून्य, 0);
अटल BIN_ATTR(DMI, S_IRUSR, raw_table_पढ़ो, शून्य, 0);

अटल पूर्णांक __init dmi_init(व्योम)
अणु
	काष्ठा kobject *tables_kobj;
	u8 *dmi_table;
	पूर्णांक ret = -ENOMEM;

	अगर (!dmi_available)
		वापस 0;

	/*
	 * Set up dmi directory at /sys/firmware/dmi. This entry should stay
	 * even after farther error, as it can be used by other modules like
	 * dmi-sysfs.
	 */
	dmi_kobj = kobject_create_and_add("dmi", firmware_kobj);
	अगर (!dmi_kobj)
		जाओ err;

	tables_kobj = kobject_create_and_add("tables", dmi_kobj);
	अगर (!tables_kobj)
		जाओ err;

	dmi_table = dmi_remap(dmi_base, dmi_len);
	अगर (!dmi_table)
		जाओ err_tables;

	bin_attr_smbios_entry_poपूर्णांक.size = smbios_entry_poपूर्णांक_size;
	bin_attr_smbios_entry_poपूर्णांक.निजी = smbios_entry_poपूर्णांक;
	ret = sysfs_create_bin_file(tables_kobj, &bin_attr_smbios_entry_poपूर्णांक);
	अगर (ret)
		जाओ err_unmap;

	bin_attr_DMI.size = dmi_len;
	bin_attr_DMI.निजी = dmi_table;
	ret = sysfs_create_bin_file(tables_kobj, &bin_attr_DMI);
	अगर (!ret)
		वापस 0;

	sysfs_हटाओ_bin_file(tables_kobj,
			      &bin_attr_smbios_entry_poपूर्णांक);
 err_unmap:
	dmi_unmap(dmi_table);
 err_tables:
	kobject_del(tables_kobj);
	kobject_put(tables_kobj);
 err:
	pr_err("dmi: Firmware registration failed.\n");

	वापस ret;
पूर्ण
subsys_initcall(dmi_init);

/**
 *	dmi_setup - scan and setup DMI प्रणाली inक्रमmation
 *
 *	Scan the DMI प्रणाली inक्रमmation. This setups DMI identअगरiers
 *	(dmi_प्रणाली_id) क्रम prपूर्णांकing it out on task dumps and prepares
 *	DIMM entry inक्रमmation (dmi_memdev_info) from the SMBIOS table
 *	क्रम using this when reporting memory errors.
 */
व्योम __init dmi_setup(व्योम)
अणु
	dmi_scan_machine();
	अगर (!dmi_available)
		वापस;

	dmi_memdev_walk();
	dump_stack_set_arch_desc("%s", dmi_ids_string);
पूर्ण

/**
 *	dmi_matches - check अगर dmi_प्रणाली_id काष्ठाure matches प्रणाली DMI data
 *	@dmi: poपूर्णांकer to the dmi_प्रणाली_id काष्ठाure to check
 */
अटल bool dmi_matches(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dmi->matches); i++) अणु
		पूर्णांक s = dmi->matches[i].slot;
		अगर (s == DMI_NONE)
			अवरोध;
		अगर (s == DMI_OEM_STRING) अणु
			/* DMI_OEM_STRING must be exact match */
			स्थिर काष्ठा dmi_device *valid;

			valid = dmi_find_device(DMI_DEV_TYPE_OEM_STRING,
						dmi->matches[i].substr, शून्य);
			अगर (valid)
				जारी;
		पूर्ण अन्यथा अगर (dmi_ident[s]) अणु
			अगर (dmi->matches[i].exact_match) अणु
				अगर (!म_भेद(dmi_ident[s],
					    dmi->matches[i].substr))
					जारी;
			पूर्ण अन्यथा अणु
				अगर (म_माला(dmi_ident[s],
					   dmi->matches[i].substr))
					जारी;
			पूर्ण
		पूर्ण

		/* No match */
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 *	dmi_is_end_of_table - check क्रम end-of-table marker
 *	@dmi: poपूर्णांकer to the dmi_प्रणाली_id काष्ठाure to check
 */
अटल bool dmi_is_end_of_table(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	वापस dmi->matches[0].slot == DMI_NONE;
पूर्ण

/**
 *	dmi_check_प्रणाली - check प्रणाली DMI data
 *	@list: array of dmi_प्रणाली_id काष्ठाures to match against
 *		All non-null elements of the list must match
 *		their slot's (field index's) data (i.e., each
 *		list string must be a substring of the specअगरied
 *		DMI slot's string data) to be considered a
 *		successful match.
 *
 *	Walk the blacklist table running matching functions until someone
 *	वापसs non zero or we hit the end. Callback function is called क्रम
 *	each successful match. Returns the number of matches.
 *
 *	dmi_setup must be called beक्रमe this function is called.
 */
पूर्णांक dmi_check_प्रणाली(स्थिर काष्ठा dmi_प्रणाली_id *list)
अणु
	पूर्णांक count = 0;
	स्थिर काष्ठा dmi_प्रणाली_id *d;

	क्रम (d = list; !dmi_is_end_of_table(d); d++)
		अगर (dmi_matches(d)) अणु
			count++;
			अगर (d->callback && d->callback(d))
				अवरोध;
		पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(dmi_check_प्रणाली);

/**
 *	dmi_first_match - find dmi_प्रणाली_id काष्ठाure matching प्रणाली DMI data
 *	@list: array of dmi_प्रणाली_id काष्ठाures to match against
 *		All non-null elements of the list must match
 *		their slot's (field index's) data (i.e., each
 *		list string must be a substring of the specअगरied
 *		DMI slot's string data) to be considered a
 *		successful match.
 *
 *	Walk the blacklist table until the first match is found.  Return the
 *	poपूर्णांकer to the matching entry or शून्य अगर there's no match.
 *
 *	dmi_setup must be called beक्रमe this function is called.
 */
स्थिर काष्ठा dmi_प्रणाली_id *dmi_first_match(स्थिर काष्ठा dmi_प्रणाली_id *list)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *d;

	क्रम (d = list; !dmi_is_end_of_table(d); d++)
		अगर (dmi_matches(d))
			वापस d;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dmi_first_match);

/**
 *	dmi_get_प्रणाली_info - वापस DMI data value
 *	@field: data index (see क्रमागत dmi_field)
 *
 *	Returns one DMI data value, can be used to perक्रमm
 *	complex DMI data checks.
 */
स्थिर अक्षर *dmi_get_प्रणाली_info(पूर्णांक field)
अणु
	वापस dmi_ident[field];
पूर्ण
EXPORT_SYMBOL(dmi_get_प्रणाली_info);

/**
 * dmi_name_in_serial - Check अगर string is in the DMI product serial inक्रमmation
 * @str: string to check क्रम
 */
पूर्णांक dmi_name_in_serial(स्थिर अक्षर *str)
अणु
	पूर्णांक f = DMI_PRODUCT_SERIAL;
	अगर (dmi_ident[f] && म_माला(dmi_ident[f], str))
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	dmi_name_in_venकरोrs - Check अगर string is in the DMI प्रणाली or board venकरोr name
 *	@str: Case sensitive Name
 */
पूर्णांक dmi_name_in_venकरोrs(स्थिर अक्षर *str)
अणु
	अटल पूर्णांक fields[] = अणु DMI_SYS_VENDOR, DMI_BOARD_VENDOR, DMI_NONE पूर्ण;
	पूर्णांक i;
	क्रम (i = 0; fields[i] != DMI_NONE; i++) अणु
		पूर्णांक f = fields[i];
		अगर (dmi_ident[f] && म_माला(dmi_ident[f], str))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dmi_name_in_venकरोrs);

/**
 *	dmi_find_device - find onboard device by type/name
 *	@type: device type or %DMI_DEV_TYPE_ANY to match all device types
 *	@name: device name string or %शून्य to match all
 *	@from: previous device found in search, or %शून्य क्रम new search.
 *
 *	Iterates through the list of known onboard devices. If a device is
 *	found with a matching @type and @name, a poपूर्णांकer to its device
 *	काष्ठाure is वापसed.  Otherwise, %शून्य is वापसed.
 *	A new search is initiated by passing %शून्य as the @from argument.
 *	If @from is not %शून्य, searches जारी from next device.
 */
स्थिर काष्ठा dmi_device *dmi_find_device(पूर्णांक type, स्थिर अक्षर *name,
				    स्थिर काष्ठा dmi_device *from)
अणु
	स्थिर काष्ठा list_head *head = from ? &from->list : &dmi_devices;
	काष्ठा list_head *d;

	क्रम (d = head->next; d != &dmi_devices; d = d->next) अणु
		स्थिर काष्ठा dmi_device *dev =
			list_entry(d, काष्ठा dmi_device, list);

		अगर (((type == DMI_DEV_TYPE_ANY) || (dev->type == type)) &&
		    ((name == शून्य) || (म_भेद(dev->name, name) == 0)))
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dmi_find_device);

/**
 *	dmi_get_date - parse a DMI date
 *	@field:	data index (see क्रमागत dmi_field)
 *	@yearp: optional out parameter क्रम the year
 *	@monthp: optional out parameter क्रम the month
 *	@dayp: optional out parameter क्रम the day
 *
 *	The date field is assumed to be in the क्रमm resembling
 *	[mm[/dd]]/yy[yy] and the result is stored in the out
 *	parameters any or all of which can be omitted.
 *
 *	If the field करोesn't exist, all out parameters are set to zero
 *	and false is वापसed.  Otherwise, true is वापसed with any
 *	invalid part of date set to zero.
 *
 *	On वापस, year, month and day are guaranteed to be in the
 *	range of [0,9999], [0,12] and [0,31] respectively.
 */
bool dmi_get_date(पूर्णांक field, पूर्णांक *yearp, पूर्णांक *monthp, पूर्णांक *dayp)
अणु
	पूर्णांक year = 0, month = 0, day = 0;
	bool exists;
	स्थिर अक्षर *s, *y;
	अक्षर *e;

	s = dmi_get_प्रणाली_info(field);
	exists = s;
	अगर (!exists)
		जाओ out;

	/*
	 * Determine year first.  We assume the date string resembles
	 * mm/dd/yy[yy] but the original code extracted only the year
	 * from the end.  Keep the behavior in the spirit of no
	 * surprises.
	 */
	y = म_खोजप(s, '/');
	अगर (!y)
		जाओ out;

	y++;
	year = simple_म_से_अदीर्घ(y, &e, 10);
	अगर (y != e && year < 100) अणु	/* 2-digit year */
		year += 1900;
		अगर (year < 1996)	/* no dates < spec 1.0 */
			year += 100;
	पूर्ण
	अगर (year > 9999)		/* year should fit in %04d */
		year = 0;

	/* parse the mm and dd */
	month = simple_म_से_अदीर्घ(s, &e, 10);
	अगर (s == e || *e != '/' || !month || month > 12) अणु
		month = 0;
		जाओ out;
	पूर्ण

	s = e + 1;
	day = simple_म_से_अदीर्घ(s, &e, 10);
	अगर (s == y || s == e || *e != '/' || day > 31)
		day = 0;
out:
	अगर (yearp)
		*yearp = year;
	अगर (monthp)
		*monthp = month;
	अगर (dayp)
		*dayp = day;
	वापस exists;
पूर्ण
EXPORT_SYMBOL(dmi_get_date);

/**
 *	dmi_get_bios_year - get a year out of DMI_BIOS_DATE field
 *
 *	Returns year on success, -ENXIO अगर DMI is not selected,
 *	or a dअगरferent negative error code अगर DMI field is not present
 *	or not parseable.
 */
पूर्णांक dmi_get_bios_year(व्योम)
अणु
	bool exists;
	पूर्णांक year;

	exists = dmi_get_date(DMI_BIOS_DATE, &year, शून्य, शून्य);
	अगर (!exists)
		वापस -ENODATA;

	वापस year ? year : -दुस्फल;
पूर्ण
EXPORT_SYMBOL(dmi_get_bios_year);

/**
 *	dmi_walk - Walk the DMI table and get called back क्रम every record
 *	@decode: Callback function
 *	@निजी_data: Private data to be passed to the callback function
 *
 *	Returns 0 on success, -ENXIO अगर DMI is not selected or not present,
 *	or a dअगरferent negative error code अगर DMI walking fails.
 */
पूर्णांक dmi_walk(व्योम (*decode)(स्थिर काष्ठा dmi_header *, व्योम *),
	     व्योम *निजी_data)
अणु
	u8 *buf;

	अगर (!dmi_available)
		वापस -ENXIO;

	buf = dmi_remap(dmi_base, dmi_len);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	dmi_decode_table(buf, decode, निजी_data);

	dmi_unmap(buf);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dmi_walk);

/**
 * dmi_match - compare a string to the dmi field (अगर exists)
 * @f: DMI field identअगरier
 * @str: string to compare the DMI field to
 *
 * Returns true अगर the requested field equals to the str (including शून्य).
 */
bool dmi_match(क्रमागत dmi_field f, स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *info = dmi_get_प्रणाली_info(f);

	अगर (info == शून्य || str == शून्य)
		वापस info == str;

	वापस !म_भेद(info, str);
पूर्ण
EXPORT_SYMBOL_GPL(dmi_match);

व्योम dmi_memdev_name(u16 handle, स्थिर अक्षर **bank, स्थिर अक्षर **device)
अणु
	पूर्णांक n;

	अगर (dmi_memdev == शून्य)
		वापस;

	क्रम (n = 0; n < dmi_memdev_nr; n++) अणु
		अगर (handle == dmi_memdev[n].handle) अणु
			*bank = dmi_memdev[n].bank;
			*device = dmi_memdev[n].device;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dmi_memdev_name);

u64 dmi_memdev_size(u16 handle)
अणु
	पूर्णांक n;

	अगर (dmi_memdev) अणु
		क्रम (n = 0; n < dmi_memdev_nr; n++) अणु
			अगर (handle == dmi_memdev[n].handle)
				वापस dmi_memdev[n].size;
		पूर्ण
	पूर्ण
	वापस ~0ull;
पूर्ण
EXPORT_SYMBOL_GPL(dmi_memdev_size);

/**
 * dmi_memdev_type - get the memory type
 * @handle: DMI काष्ठाure handle
 *
 * Return the DMI memory type of the module in the slot associated with the
 * given DMI handle, or 0x0 अगर no such DMI handle exists.
 */
u8 dmi_memdev_type(u16 handle)
अणु
	पूर्णांक n;

	अगर (dmi_memdev) अणु
		क्रम (n = 0; n < dmi_memdev_nr; n++) अणु
			अगर (handle == dmi_memdev[n].handle)
				वापस dmi_memdev[n].type;
		पूर्ण
	पूर्ण
	वापस 0x0;	/* Not a valid value */
पूर्ण
EXPORT_SYMBOL_GPL(dmi_memdev_type);

/**
 *	dmi_memdev_handle - get the DMI handle of a memory slot
 *	@slot: slot number
 *
 *	Return the DMI handle associated with a given memory slot, or %0xFFFF
 *      अगर there is no such slot.
 */
u16 dmi_memdev_handle(पूर्णांक slot)
अणु
	अगर (dmi_memdev && slot >= 0 && slot < dmi_memdev_nr)
		वापस dmi_memdev[slot].handle;

	वापस 0xffff;	/* Not a valid value */
पूर्ण
EXPORT_SYMBOL_GPL(dmi_memdev_handle);
