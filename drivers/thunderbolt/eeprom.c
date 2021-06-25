<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - eeprom access
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश "tb.h"

/*
 * tb_eeprom_ctl_ग_लिखो() - ग_लिखो control word
 */
अटल पूर्णांक tb_eeprom_ctl_ग_लिखो(काष्ठा tb_चयन *sw, काष्ठा tb_eeprom_ctl *ctl)
अणु
	वापस tb_sw_ग_लिखो(sw, ctl, TB_CFG_SWITCH, sw->cap_plug_events + 4, 1);
पूर्ण

/*
 * tb_eeprom_ctl_ग_लिखो() - पढ़ो control word
 */
अटल पूर्णांक tb_eeprom_ctl_पढ़ो(काष्ठा tb_चयन *sw, काष्ठा tb_eeprom_ctl *ctl)
अणु
	वापस tb_sw_पढ़ो(sw, ctl, TB_CFG_SWITCH, sw->cap_plug_events + 4, 1);
पूर्ण

क्रमागत tb_eeprom_transfer अणु
	TB_EEPROM_IN,
	TB_EEPROM_OUT,
पूर्ण;

/*
 * tb_eeprom_active - enable rom access
 *
 * WARNING: Always disable access after usage. Otherwise the controller will
 * fail to reprobe.
 */
अटल पूर्णांक tb_eeprom_active(काष्ठा tb_चयन *sw, bool enable)
अणु
	काष्ठा tb_eeprom_ctl ctl;
	पूर्णांक res = tb_eeprom_ctl_पढ़ो(sw, &ctl);
	अगर (res)
		वापस res;
	अगर (enable) अणु
		ctl.access_high = 1;
		res = tb_eeprom_ctl_ग_लिखो(sw, &ctl);
		अगर (res)
			वापस res;
		ctl.access_low = 0;
		वापस tb_eeprom_ctl_ग_लिखो(sw, &ctl);
	पूर्ण अन्यथा अणु
		ctl.access_low = 1;
		res = tb_eeprom_ctl_ग_लिखो(sw, &ctl);
		अगर (res)
			वापस res;
		ctl.access_high = 0;
		वापस tb_eeprom_ctl_ग_लिखो(sw, &ctl);
	पूर्ण
पूर्ण

/*
 * tb_eeprom_transfer - transfer one bit
 *
 * If TB_EEPROM_IN is passed, then the bit can be retrieved from ctl->data_in.
 * If TB_EEPROM_OUT is passed, then ctl->data_out will be written.
 */
अटल पूर्णांक tb_eeprom_transfer(काष्ठा tb_चयन *sw, काष्ठा tb_eeprom_ctl *ctl,
			      क्रमागत tb_eeprom_transfer direction)
अणु
	पूर्णांक res;
	अगर (direction == TB_EEPROM_OUT) अणु
		res = tb_eeprom_ctl_ग_लिखो(sw, ctl);
		अगर (res)
			वापस res;
	पूर्ण
	ctl->घड़ी = 1;
	res = tb_eeprom_ctl_ग_लिखो(sw, ctl);
	अगर (res)
		वापस res;
	अगर (direction == TB_EEPROM_IN) अणु
		res = tb_eeprom_ctl_पढ़ो(sw, ctl);
		अगर (res)
			वापस res;
	पूर्ण
	ctl->घड़ी = 0;
	वापस tb_eeprom_ctl_ग_लिखो(sw, ctl);
पूर्ण

/*
 * tb_eeprom_out - ग_लिखो one byte to the bus
 */
अटल पूर्णांक tb_eeprom_out(काष्ठा tb_चयन *sw, u8 val)
अणु
	काष्ठा tb_eeprom_ctl ctl;
	पूर्णांक i;
	पूर्णांक res = tb_eeprom_ctl_पढ़ो(sw, &ctl);
	अगर (res)
		वापस res;
	क्रम (i = 0; i < 8; i++) अणु
		ctl.data_out = val & 0x80;
		res = tb_eeprom_transfer(sw, &ctl, TB_EEPROM_OUT);
		अगर (res)
			वापस res;
		val <<= 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * tb_eeprom_in - पढ़ो one byte from the bus
 */
अटल पूर्णांक tb_eeprom_in(काष्ठा tb_चयन *sw, u8 *val)
अणु
	काष्ठा tb_eeprom_ctl ctl;
	पूर्णांक i;
	पूर्णांक res = tb_eeprom_ctl_पढ़ो(sw, &ctl);
	अगर (res)
		वापस res;
	*val = 0;
	क्रम (i = 0; i < 8; i++) अणु
		*val <<= 1;
		res = tb_eeprom_transfer(sw, &ctl, TB_EEPROM_IN);
		अगर (res)
			वापस res;
		*val |= ctl.data_in;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * tb_eeprom_get_drom_offset - get drom offset within eeprom
 */
अटल पूर्णांक tb_eeprom_get_drom_offset(काष्ठा tb_चयन *sw, u16 *offset)
अणु
	काष्ठा tb_cap_plug_events cap;
	पूर्णांक res;

	अगर (!sw->cap_plug_events) अणु
		tb_sw_warn(sw, "no TB_CAP_PLUG_EVENTS, cannot read eeprom\n");
		वापस -ENODEV;
	पूर्ण
	res = tb_sw_पढ़ो(sw, &cap, TB_CFG_SWITCH, sw->cap_plug_events,
			     माप(cap) / 4);
	अगर (res)
		वापस res;

	अगर (!cap.eeprom_ctl.present || cap.eeprom_ctl.not_present) अणु
		tb_sw_warn(sw, "no NVM\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cap.drom_offset > 0xffff) अणु
		tb_sw_warn(sw, "drom offset is larger than 0xffff: %#x\n",
				cap.drom_offset);
		वापस -ENXIO;
	पूर्ण
	*offset = cap.drom_offset;
	वापस 0;
पूर्ण

/*
 * tb_eeprom_पढ़ो_n - पढ़ो count bytes from offset पूर्णांकo val
 */
अटल पूर्णांक tb_eeprom_पढ़ो_n(काष्ठा tb_चयन *sw, u16 offset, u8 *val,
		माप_प्रकार count)
अणु
	u16 drom_offset;
	पूर्णांक i, res;

	res = tb_eeprom_get_drom_offset(sw, &drom_offset);
	अगर (res)
		वापस res;

	offset += drom_offset;

	res = tb_eeprom_active(sw, true);
	अगर (res)
		वापस res;
	res = tb_eeprom_out(sw, 3);
	अगर (res)
		वापस res;
	res = tb_eeprom_out(sw, offset >> 8);
	अगर (res)
		वापस res;
	res = tb_eeprom_out(sw, offset);
	अगर (res)
		वापस res;
	क्रम (i = 0; i < count; i++) अणु
		res = tb_eeprom_in(sw, val + i);
		अगर (res)
			वापस res;
	पूर्ण
	वापस tb_eeprom_active(sw, false);
पूर्ण

अटल u8 tb_crc8(u8 *data, पूर्णांक len)
अणु
	पूर्णांक i, j;
	u8 val = 0xff;
	क्रम (i = 0; i < len; i++) अणु
		val ^= data[i];
		क्रम (j = 0; j < 8; j++)
			val = (val << 1) ^ ((val & 0x80) ? 7 : 0);
	पूर्ण
	वापस val;
पूर्ण

अटल u32 tb_crc32(व्योम *data, माप_प्रकार len)
अणु
	वापस ~__crc32c_le(~0, data, len);
पूर्ण

#घोषणा TB_DROM_DATA_START 13
काष्ठा tb_drom_header अणु
	/* BYTE 0 */
	u8 uid_crc8; /* checksum क्रम uid */
	/* BYTES 1-8 */
	u64 uid;
	/* BYTES 9-12 */
	u32 data_crc32; /* checksum क्रम data_len bytes starting at byte 13 */
	/* BYTE 13 */
	u8 device_rom_revision; /* should be <= 1 */
	u16 data_len:10;
	u8 __unknown1:6;
	/* BYTES 16-21 */
	u16 venकरोr_id;
	u16 model_id;
	u8 model_rev;
	u8 eeprom_rev;
पूर्ण __packed;

क्रमागत tb_drom_entry_type अणु
	/* क्रमce अचिन्हित to prevent "one-bit signed bitfield" warning */
	TB_DROM_ENTRY_GENERIC = 0U,
	TB_DROM_ENTRY_PORT,
पूर्ण;

काष्ठा tb_drom_entry_header अणु
	u8 len;
	u8 index:6;
	bool port_disabled:1; /* only valid अगर type is TB_DROM_ENTRY_PORT */
	क्रमागत tb_drom_entry_type type:1;
पूर्ण __packed;

काष्ठा tb_drom_entry_generic अणु
	काष्ठा tb_drom_entry_header header;
	u8 data[];
पूर्ण __packed;

काष्ठा tb_drom_entry_port अणु
	/* BYTES 0-1 */
	काष्ठा tb_drom_entry_header header;
	/* BYTE 2 */
	u8 dual_link_port_rid:4;
	u8 link_nr:1;
	u8 unknown1:2;
	bool has_dual_link_port:1;

	/* BYTE 3 */
	u8 dual_link_port_nr:6;
	u8 unknown2:2;

	/* BYTES 4 - 5 TODO decode */
	u8 micro2:4;
	u8 micro1:4;
	u8 micro3;

	/* BYTES 6-7, TODO: verअगरy (find hardware that has these set) */
	u8 peer_port_rid:4;
	u8 unknown3:3;
	bool has_peer_port:1;
	u8 peer_port_nr:6;
	u8 unknown4:2;
पूर्ण __packed;

/* USB4 product descriptor */
काष्ठा tb_drom_entry_desc अणु
	काष्ठा tb_drom_entry_header header;
	u16 bcdUSBSpec;
	u16 idVenकरोr;
	u16 idProduct;
	u16 bcdProductFWRevision;
	u32 TID;
	u8 productHWRevision;
पूर्ण;

/**
 * tb_drom_पढ़ो_uid_only() - Read UID directly from DROM
 * @sw: Router whose UID to पढ़ो
 * @uid: UID is placed here
 *
 * Does not use the cached copy in sw->drom. Used during resume to check चयन
 * identity.
 */
पूर्णांक tb_drom_पढ़ो_uid_only(काष्ठा tb_चयन *sw, u64 *uid)
अणु
	u8 data[9];
	u8 crc;
	पूर्णांक res;

	/* पढ़ो uid */
	res = tb_eeprom_पढ़ो_n(sw, 0, data, 9);
	अगर (res)
		वापस res;

	crc = tb_crc8(data + 1, 8);
	अगर (crc != data[0]) अणु
		tb_sw_warn(sw, "uid crc8 mismatch (expected: %#x, got: %#x)\n",
				data[0], crc);
		वापस -EIO;
	पूर्ण

	*uid = *(u64 *)(data+1);
	वापस 0;
पूर्ण

अटल पूर्णांक tb_drom_parse_entry_generic(काष्ठा tb_चयन *sw,
		काष्ठा tb_drom_entry_header *header)
अणु
	स्थिर काष्ठा tb_drom_entry_generic *entry =
		(स्थिर काष्ठा tb_drom_entry_generic *)header;

	चयन (header->index) अणु
	हाल 1:
		/* Length includes 2 bytes header so हटाओ it beक्रमe copy */
		sw->venकरोr_name = kstrndup(entry->data,
			header->len - माप(*header), GFP_KERNEL);
		अगर (!sw->venकरोr_name)
			वापस -ENOMEM;
		अवरोध;

	हाल 2:
		sw->device_name = kstrndup(entry->data,
			header->len - माप(*header), GFP_KERNEL);
		अगर (!sw->device_name)
			वापस -ENOMEM;
		अवरोध;
	हाल 9: अणु
		स्थिर काष्ठा tb_drom_entry_desc *desc =
			(स्थिर काष्ठा tb_drom_entry_desc *)entry;

		अगर (!sw->venकरोr && !sw->device) अणु
			sw->venकरोr = desc->idVenकरोr;
			sw->device = desc->idProduct;
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb_drom_parse_entry_port(काष्ठा tb_चयन *sw,
				    काष्ठा tb_drom_entry_header *header)
अणु
	काष्ठा tb_port *port;
	पूर्णांक res;
	क्रमागत tb_port_type type;

	/*
	 * Some DROMs list more ports than the controller actually has
	 * so we skip those but allow the parser to जारी.
	 */
	अगर (header->index > sw->config.max_port_number) अणु
		dev_info_once(&sw->dev, "ignoring unnecessary extra entries in DROM\n");
		वापस 0;
	पूर्ण

	port = &sw->ports[header->index];
	port->disabled = header->port_disabled;
	अगर (port->disabled)
		वापस 0;

	res = tb_port_पढ़ो(port, &type, TB_CFG_PORT, 2, 1);
	अगर (res)
		वापस res;
	type &= 0xffffff;

	अगर (type == TB_TYPE_PORT) अणु
		काष्ठा tb_drom_entry_port *entry = (व्योम *) header;
		अगर (header->len != माप(*entry)) अणु
			tb_sw_warn(sw,
				"port entry has size %#x (expected %#zx)\n",
				header->len, माप(काष्ठा tb_drom_entry_port));
			वापस -EIO;
		पूर्ण
		port->link_nr = entry->link_nr;
		अगर (entry->has_dual_link_port)
			port->dual_link_port =
				&port->sw->ports[entry->dual_link_port_nr];
	पूर्ण
	वापस 0;
पूर्ण

/*
 * tb_drom_parse_entries - parse the linked list of drom entries
 *
 * Drom must have been copied to sw->drom.
 */
अटल पूर्णांक tb_drom_parse_entries(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_drom_header *header = (व्योम *) sw->drom;
	u16 pos = माप(*header);
	u16 drom_size = header->data_len + TB_DROM_DATA_START;
	पूर्णांक res;

	जबतक (pos < drom_size) अणु
		काष्ठा tb_drom_entry_header *entry = (व्योम *) (sw->drom + pos);
		अगर (pos + 1 == drom_size || pos + entry->len > drom_size
				|| !entry->len) अणु
			tb_sw_warn(sw, "DROM buffer overrun\n");
			वापस -EILSEQ;
		पूर्ण

		चयन (entry->type) अणु
		हाल TB_DROM_ENTRY_GENERIC:
			res = tb_drom_parse_entry_generic(sw, entry);
			अवरोध;
		हाल TB_DROM_ENTRY_PORT:
			res = tb_drom_parse_entry_port(sw, entry);
			अवरोध;
		पूर्ण
		अगर (res)
			वापस res;

		pos += entry->len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * tb_drom_copy_efi - copy drom supplied by EFI to sw->drom अगर present
 */
अटल पूर्णांक tb_drom_copy_efi(काष्ठा tb_चयन *sw, u16 *size)
अणु
	काष्ठा device *dev = &sw->tb->nhi->pdev->dev;
	पूर्णांक len, res;

	len = device_property_count_u8(dev, "ThunderboltDROM");
	अगर (len < 0 || len < माप(काष्ठा tb_drom_header))
		वापस -EINVAL;

	sw->drom = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!sw->drom)
		वापस -ENOMEM;

	res = device_property_पढ़ो_u8_array(dev, "ThunderboltDROM", sw->drom,
									len);
	अगर (res)
		जाओ err;

	*size = ((काष्ठा tb_drom_header *)sw->drom)->data_len +
							  TB_DROM_DATA_START;
	अगर (*size > len)
		जाओ err;

	वापस 0;

err:
	kमुक्त(sw->drom);
	sw->drom = शून्य;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tb_drom_copy_nvm(काष्ठा tb_चयन *sw, u16 *size)
अणु
	u32 drom_offset;
	पूर्णांक ret;

	अगर (!sw->dma_port)
		वापस -ENODEV;

	ret = tb_sw_पढ़ो(sw, &drom_offset, TB_CFG_SWITCH,
			 sw->cap_plug_events + 12, 1);
	अगर (ret)
		वापस ret;

	अगर (!drom_offset)
		वापस -ENODEV;

	ret = dma_port_flash_पढ़ो(sw->dma_port, drom_offset + 14, size,
				  माप(*size));
	अगर (ret)
		वापस ret;

	/* Size includes CRC8 + UID + CRC32 */
	*size += 1 + 8 + 4;
	sw->drom = kzalloc(*size, GFP_KERNEL);
	अगर (!sw->drom)
		वापस -ENOMEM;

	ret = dma_port_flash_पढ़ो(sw->dma_port, drom_offset, sw->drom, *size);
	अगर (ret)
		जाओ err_मुक्त;

	/*
	 * Read UID from the minimal DROM because the one in NVM is just
	 * a placeholder.
	 */
	tb_drom_पढ़ो_uid_only(sw, &sw->uid);
	वापस 0;

err_मुक्त:
	kमुक्त(sw->drom);
	sw->drom = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक usb4_copy_host_drom(काष्ठा tb_चयन *sw, u16 *size)
अणु
	पूर्णांक ret;

	ret = usb4_चयन_drom_पढ़ो(sw, 14, size, माप(*size));
	अगर (ret)
		वापस ret;

	/* Size includes CRC8 + UID + CRC32 */
	*size += 1 + 8 + 4;
	sw->drom = kzalloc(*size, GFP_KERNEL);
	अगर (!sw->drom)
		वापस -ENOMEM;

	ret = usb4_चयन_drom_पढ़ो(sw, 0, sw->drom, *size);
	अगर (ret) अणु
		kमुक्त(sw->drom);
		sw->drom = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tb_drom_पढ़ो_n(काष्ठा tb_चयन *sw, u16 offset, u8 *val,
			  माप_प्रकार count)
अणु
	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_drom_पढ़ो(sw, offset, val, count);
	वापस tb_eeprom_पढ़ो_n(sw, offset, val, count);
पूर्ण

अटल पूर्णांक tb_drom_parse(काष्ठा tb_चयन *sw)
अणु
	स्थिर काष्ठा tb_drom_header *header =
		(स्थिर काष्ठा tb_drom_header *)sw->drom;
	u32 crc;

	crc = tb_crc8((u8 *) &header->uid, 8);
	अगर (crc != header->uid_crc8) अणु
		tb_sw_warn(sw,
			"DROM UID CRC8 mismatch (expected: %#x, got: %#x), aborting\n",
			header->uid_crc8, crc);
		वापस -EINVAL;
	पूर्ण
	अगर (!sw->uid)
		sw->uid = header->uid;
	sw->venकरोr = header->venकरोr_id;
	sw->device = header->model_id;

	crc = tb_crc32(sw->drom + TB_DROM_DATA_START, header->data_len);
	अगर (crc != header->data_crc32) अणु
		tb_sw_warn(sw,
			"DROM data CRC32 mismatch (expected: %#x, got: %#x), continuing\n",
			header->data_crc32, crc);
	पूर्ण

	वापस tb_drom_parse_entries(sw);
पूर्ण

अटल पूर्णांक usb4_drom_parse(काष्ठा tb_चयन *sw)
अणु
	स्थिर काष्ठा tb_drom_header *header =
		(स्थिर काष्ठा tb_drom_header *)sw->drom;
	u32 crc;

	crc = tb_crc32(sw->drom + TB_DROM_DATA_START, header->data_len);
	अगर (crc != header->data_crc32) अणु
		tb_sw_warn(sw,
			   "DROM data CRC32 mismatch (expected: %#x, got: %#x), aborting\n",
			   header->data_crc32, crc);
		वापस -EINVAL;
	पूर्ण

	वापस tb_drom_parse_entries(sw);
पूर्ण

/**
 * tb_drom_पढ़ो() - Copy DROM to sw->drom and parse it
 * @sw: Router whose DROM to पढ़ो and parse
 *
 * This function पढ़ोs router DROM and अगर successful parses the entries and
 * populates the fields in @sw accordingly. Can be called क्रम any router
 * generation.
 *
 * Returns %0 in हाल of success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_drom_पढ़ो(काष्ठा tb_चयन *sw)
अणु
	u16 size;
	काष्ठा tb_drom_header *header;
	पूर्णांक res, retries = 1;

	अगर (sw->drom)
		वापस 0;

	अगर (tb_route(sw) == 0) अणु
		/*
		 * Apple's NHI EFI driver supplies a DROM क्रम the root चयन
		 * in a device property. Use it अगर available.
		 */
		अगर (tb_drom_copy_efi(sw, &size) == 0)
			जाओ parse;

		/* Non-Apple hardware has the DROM as part of NVM */
		अगर (tb_drom_copy_nvm(sw, &size) == 0)
			जाओ parse;

		/*
		 * USB4 hosts may support पढ़ोing DROM through router
		 * operations.
		 */
		अगर (tb_चयन_is_usb4(sw)) अणु
			usb4_चयन_पढ़ो_uid(sw, &sw->uid);
			अगर (!usb4_copy_host_drom(sw, &size))
				जाओ parse;
		पूर्ण अन्यथा अणु
			/*
			 * The root चयन contains only a dummy drom
			 * (header only, no entries). Hardcode the
			 * configuration here.
			 */
			tb_drom_पढ़ो_uid_only(sw, &sw->uid);
		पूर्ण

		वापस 0;
	पूर्ण

	res = tb_drom_पढ़ो_n(sw, 14, (u8 *) &size, 2);
	अगर (res)
		वापस res;
	size &= 0x3ff;
	size += TB_DROM_DATA_START;
	tb_sw_dbg(sw, "reading drom (length: %#x)\n", size);
	अगर (size < माप(*header)) अणु
		tb_sw_warn(sw, "drom too small, aborting\n");
		वापस -EIO;
	पूर्ण

	sw->drom = kzalloc(size, GFP_KERNEL);
	अगर (!sw->drom)
		वापस -ENOMEM;
	res = tb_drom_पढ़ो_n(sw, 0, sw->drom, size);
	अगर (res)
		जाओ err;

parse:
	header = (व्योम *) sw->drom;

	अगर (header->data_len + TB_DROM_DATA_START != size) अणु
		tb_sw_warn(sw, "drom size mismatch, aborting\n");
		जाओ err;
	पूर्ण

	tb_sw_dbg(sw, "DROM version: %d\n", header->device_rom_revision);

	चयन (header->device_rom_revision) अणु
	हाल 3:
		res = usb4_drom_parse(sw);
		अवरोध;
	शेष:
		tb_sw_warn(sw, "DROM device_rom_revision %#x unknown\n",
			   header->device_rom_revision);
		fallthrough;
	हाल 1:
		res = tb_drom_parse(sw);
		अवरोध;
	पूर्ण

	/* If the DROM parsing fails, रुको a moment and retry once */
	अगर (res == -EILSEQ && retries--) अणु
		tb_sw_warn(sw, "parsing DROM failed, retrying\n");
		msleep(100);
		res = tb_drom_पढ़ो_n(sw, 0, sw->drom, size);
		अगर (!res)
			जाओ parse;
	पूर्ण

	अगर (!res)
		वापस 0;

err:
	kमुक्त(sw->drom);
	sw->drom = शून्य;
	वापस -EIO;
पूर्ण
