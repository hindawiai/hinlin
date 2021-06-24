<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2016-2018, 2020, The Linux Foundation. All rights reserved. */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>

#समावेश <soc/qcom/cmd-db.h>

#घोषणा NUM_PRIORITY		2
#घोषणा MAX_SLV_ID		8
#घोषणा SLAVE_ID_MASK		0x7
#घोषणा SLAVE_ID_SHIFT		16

/**
 * काष्ठा entry_header: header क्रम each entry in cmddb
 *
 * @id: resource's identअगरier
 * @priority: unused
 * @addr: the address of the resource
 * @len: length of the data
 * @offset: offset from :@data_offset, start of the data
 */
काष्ठा entry_header अणु
	u8 id[8];
	__le32 priority[NUM_PRIORITY];
	__le32 addr;
	__le16 len;
	__le16 offset;
पूर्ण;

/**
 * काष्ठा rsc_hdr: resource header inक्रमmation
 *
 * @slv_id: id क्रम the resource
 * @header_offset: entry's header at offset from the end of the cmd_db_header
 * @data_offset: entry's data at offset from the end of the cmd_db_header
 * @cnt: number of entries क्रम HW type
 * @version: MSB is major, LSB is minor
 * @reserved: reserved क्रम future use.
 */
काष्ठा rsc_hdr अणु
	__le16 slv_id;
	__le16 header_offset;
	__le16 data_offset;
	__le16 cnt;
	__le16 version;
	__le16 reserved[3];
पूर्ण;

/**
 * काष्ठा cmd_db_header: The DB header inक्रमmation
 *
 * @version: The cmd db version
 * @magic: स्थिरant expected in the database
 * @header: array of resources
 * @checksum: checksum क्रम the header. Unused.
 * @reserved: reserved memory
 * @data: driver specअगरic data
 */
काष्ठा cmd_db_header अणु
	__le32 version;
	u8 magic[4];
	काष्ठा rsc_hdr header[MAX_SLV_ID];
	__le32 checksum;
	__le32 reserved;
	u8 data[];
पूर्ण;

/**
 * DOC: Description of the Command DB database.
 *
 * At the start of the command DB memory is the cmd_db_header काष्ठाure.
 * The cmd_db_header holds the version, checksum, magic key as well as an
 * array क्रम header क्रम each slave (depicted by the rsc_header). Each h/w
 * based accelerator is a 'slave' (shared resource) and has slave id indicating
 * the type of accelerator. The rsc_header is the header क्रम such inभागidual
 * slaves of a given type. The entries क्रम each of these slaves begin at the
 * rsc_hdr.header_offset. In addition each slave could have auxiliary data
 * that may be needed by the driver. The data क्रम the slave starts at the
 * entry_header.offset to the location poपूर्णांकed to by the rsc_hdr.data_offset.
 *
 * Drivers have a stringअगरied key to a slave/resource. They can query the slave
 * inक्रमmation and get the slave id and the auxiliary data and the length of the
 * data. Using this inक्रमmation, they can क्रमmat the request to be sent to the
 * h/w accelerator and request a resource state.
 */

अटल स्थिर u8 CMD_DB_MAGIC[] = अणु 0xdb, 0x30, 0x03, 0x0c पूर्ण;

अटल bool cmd_db_magic_matches(स्थिर काष्ठा cmd_db_header *header)
अणु
	स्थिर u8 *magic = header->magic;

	वापस स_भेद(magic, CMD_DB_MAGIC, ARRAY_SIZE(CMD_DB_MAGIC)) == 0;
पूर्ण

अटल काष्ठा cmd_db_header *cmd_db_header;

अटल अंतरभूत स्थिर व्योम *rsc_to_entry_header(स्थिर काष्ठा rsc_hdr *hdr)
अणु
	u16 offset = le16_to_cpu(hdr->header_offset);

	वापस cmd_db_header->data + offset;
पूर्ण

अटल अंतरभूत व्योम *
rsc_offset(स्थिर काष्ठा rsc_hdr *hdr, स्थिर काष्ठा entry_header *ent)
अणु
	u16 offset = le16_to_cpu(hdr->data_offset);
	u16 loffset = le16_to_cpu(ent->offset);

	वापस cmd_db_header->data + offset + loffset;
पूर्ण

/**
 * cmd_db_पढ़ोy - Indicates अगर command DB is available
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
पूर्णांक cmd_db_पढ़ोy(व्योम)
अणु
	अगर (cmd_db_header == शून्य)
		वापस -EPROBE_DEFER;
	अन्यथा अगर (!cmd_db_magic_matches(cmd_db_header))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cmd_db_पढ़ोy);

अटल पूर्णांक cmd_db_get_header(स्थिर अक्षर *id, स्थिर काष्ठा entry_header **eh,
			     स्थिर काष्ठा rsc_hdr **rh)
अणु
	स्थिर काष्ठा rsc_hdr *rsc_hdr;
	स्थिर काष्ठा entry_header *ent;
	पूर्णांक ret, i, j;
	u8 query[8];

	ret = cmd_db_पढ़ोy();
	अगर (ret)
		वापस ret;

	/* Pad out query string to same length as in DB */
	म_नकलन(query, id, माप(query));

	क्रम (i = 0; i < MAX_SLV_ID; i++) अणु
		rsc_hdr = &cmd_db_header->header[i];
		अगर (!rsc_hdr->slv_id)
			अवरोध;

		ent = rsc_to_entry_header(rsc_hdr);
		क्रम (j = 0; j < le16_to_cpu(rsc_hdr->cnt); j++, ent++) अणु
			अगर (स_भेद(ent->id, query, माप(ent->id)) == 0) अणु
				अगर (eh)
					*eh = ent;
				अगर (rh)
					*rh = rsc_hdr;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * cmd_db_पढ़ो_addr() - Query command db क्रम resource id address.
 *
 * @id: resource id to query क्रम address
 *
 * Return: resource address on success, 0 on error
 *
 * This is used to retrieve resource address based on resource
 * id.
 */
u32 cmd_db_पढ़ो_addr(स्थिर अक्षर *id)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा entry_header *ent;

	ret = cmd_db_get_header(id, &ent, शून्य);

	वापस ret < 0 ? 0 : le32_to_cpu(ent->addr);
पूर्ण
EXPORT_SYMBOL(cmd_db_पढ़ो_addr);

/**
 * cmd_db_पढ़ो_aux_data() - Query command db क्रम aux data.
 *
 *  @id: Resource to retrieve AUX Data on
 *  @len: size of data buffer वापसed
 *
 *  Return: poपूर्णांकer to data on success, error poपूर्णांकer otherwise
 */
स्थिर व्योम *cmd_db_पढ़ो_aux_data(स्थिर अक्षर *id, माप_प्रकार *len)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा entry_header *ent;
	स्थिर काष्ठा rsc_hdr *rsc_hdr;

	ret = cmd_db_get_header(id, &ent, &rsc_hdr);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (len)
		*len = le16_to_cpu(ent->len);

	वापस rsc_offset(rsc_hdr, ent);
पूर्ण
EXPORT_SYMBOL(cmd_db_पढ़ो_aux_data);

/**
 * cmd_db_पढ़ो_slave_id - Get the slave ID क्रम a given resource address
 *
 * @id: Resource id to query the DB क्रम version
 *
 * Return: cmd_db_hw_type क्रमागत on success, CMD_DB_HW_INVALID on error
 */
क्रमागत cmd_db_hw_type cmd_db_पढ़ो_slave_id(स्थिर अक्षर *id)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा entry_header *ent;
	u32 addr;

	ret = cmd_db_get_header(id, &ent, शून्य);
	अगर (ret < 0)
		वापस CMD_DB_HW_INVALID;

	addr = le32_to_cpu(ent->addr);
	वापस (addr >> SLAVE_ID_SHIFT) & SLAVE_ID_MASK;
पूर्ण
EXPORT_SYMBOL(cmd_db_पढ़ो_slave_id);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक cmd_db_debugfs_dump(काष्ठा seq_file *seq, व्योम *p)
अणु
	पूर्णांक i, j;
	स्थिर काष्ठा rsc_hdr *rsc;
	स्थिर काष्ठा entry_header *ent;
	स्थिर अक्षर *name;
	u16 len, version;
	u8 major, minor;

	seq_माला_दो(seq, "Command DB DUMP\n");

	क्रम (i = 0; i < MAX_SLV_ID; i++) अणु
		rsc = &cmd_db_header->header[i];
		अगर (!rsc->slv_id)
			अवरोध;

		चयन (le16_to_cpu(rsc->slv_id)) अणु
		हाल CMD_DB_HW_ARC:
			name = "ARC";
			अवरोध;
		हाल CMD_DB_HW_VRM:
			name = "VRM";
			अवरोध;
		हाल CMD_DB_HW_BCM:
			name = "BCM";
			अवरोध;
		शेष:
			name = "Unknown";
			अवरोध;
		पूर्ण

		version = le16_to_cpu(rsc->version);
		major = version >> 8;
		minor = version;

		seq_म_लिखो(seq, "Slave %s (v%u.%u)\n", name, major, minor);
		seq_माला_दो(seq, "-------------------------\n");

		ent = rsc_to_entry_header(rsc);
		क्रम (j = 0; j < le16_to_cpu(rsc->cnt); j++, ent++) अणु
			seq_म_लिखो(seq, "0x%05x: %*pEp", le32_to_cpu(ent->addr),
				   (पूर्णांक)माप(ent->id), ent->id);

			len = le16_to_cpu(ent->len);
			अगर (len) अणु
				seq_म_लिखो(seq, " [%*ph]",
					   len, rsc_offset(rsc, ent));
			पूर्ण
			seq_अ_दो(seq, '\n');
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_cmd_db_debugfs(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cmd_db_debugfs_dump, inode->i_निजी);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations cmd_db_debugfs_ops = अणु
#अगर_घोषित CONFIG_DEBUG_FS
	.खोलो = खोलो_cmd_db_debugfs,
#पूर्ण_अगर
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक cmd_db_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reserved_mem *rmem;
	पूर्णांक ret = 0;

	rmem = of_reserved_mem_lookup(pdev->dev.of_node);
	अगर (!rmem) अणु
		dev_err(&pdev->dev, "failed to acquire memory region\n");
		वापस -EINVAL;
	पूर्ण

	cmd_db_header = memremap(rmem->base, rmem->size, MEMREMAP_WB);
	अगर (!cmd_db_header) अणु
		ret = -ENOMEM;
		cmd_db_header = शून्य;
		वापस ret;
	पूर्ण

	अगर (!cmd_db_magic_matches(cmd_db_header)) अणु
		dev_err(&pdev->dev, "Invalid Command DB Magic\n");
		वापस -EINVAL;
	पूर्ण

	debugfs_create_file("cmd-db", 0400, शून्य, शून्य, &cmd_db_debugfs_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cmd_db_match_table[] = अणु
	अणु .compatible = "qcom,cmd-db" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cmd_db_match_table);

अटल काष्ठा platक्रमm_driver cmd_db_dev_driver = अणु
	.probe  = cmd_db_dev_probe,
	.driver = अणु
		   .name = "cmd-db",
		   .of_match_table = cmd_db_match_table,
		   .suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cmd_db_device_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cmd_db_dev_driver);
पूर्ण
arch_initcall(cmd_db_device_init);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. Command DB Driver");
MODULE_LICENSE("GPL v2");
