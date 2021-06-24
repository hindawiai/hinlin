<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  c 2001 PPC 64 Team, IBM Corp
 *
 * /dev/nvram driver क्रम PPC64
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/nvram.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pstore.h>
#समावेश <linux/zlib.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>

#अघोषित DEBUG_NVRAM

#घोषणा NVRAM_HEADER_LEN	माप(काष्ठा nvram_header)
#घोषणा NVRAM_BLOCK_LEN		NVRAM_HEADER_LEN

/* If change this size, then change the size of NVNAME_LEN */
काष्ठा nvram_header अणु
	अचिन्हित अक्षर signature;
	अचिन्हित अक्षर checksum;
	अचिन्हित लघु length;
	/* Terminating null required only क्रम names < 12 अक्षरs. */
	अक्षर name[12];
पूर्ण;

काष्ठा nvram_partition अणु
	काष्ठा list_head partition;
	काष्ठा nvram_header header;
	अचिन्हित पूर्णांक index;
पूर्ण;

अटल LIST_HEAD(nvram_partitions);

#अगर_घोषित CONFIG_PPC_PSERIES
काष्ठा nvram_os_partition rtas_log_partition = अणु
	.name = "ibm,rtas-log",
	.req_size = 2079,
	.min_size = 1055,
	.index = -1,
	.os_partition = true
पूर्ण;
#पूर्ण_अगर

काष्ठा nvram_os_partition oops_log_partition = अणु
	.name = "lnx,oops-log",
	.req_size = 4000,
	.min_size = 2000,
	.index = -1,
	.os_partition = true
पूर्ण;

अटल स्थिर अक्षर *nvram_os_partitions[] = अणु
#अगर_घोषित CONFIG_PPC_PSERIES
	"ibm,rtas-log",
#पूर्ण_अगर
	"lnx,oops-log",
	शून्य
पूर्ण;

अटल व्योम oops_to_nvram(काष्ठा kmsg_dumper *dumper,
			  क्रमागत kmsg_dump_reason reason);

अटल काष्ठा kmsg_dumper nvram_kmsg_dumper = अणु
	.dump = oops_to_nvram
पूर्ण;

/*
 * For capturing and compressing an oops or panic report...

 * big_oops_buf[] holds the uncompressed text we're capturing.
 *
 * oops_buf[] holds the compressed text, preceded by a oops header.
 * oops header has u16 holding the version of oops header (to dअगरferentiate
 * between old and new क्रमmat header) followed by u16 holding the length of
 * the compressed* text (*Or uncompressed, अगर compression fails.) and u64
 * holding the बारtamp. oops_buf[] माला_लो written to NVRAM.
 *
 * oops_log_info poपूर्णांकs to the header. oops_data poपूर्णांकs to the compressed text.
 *
 * +- oops_buf
 * |                                   +- oops_data
 * v                                   v
 * +-----------+-----------+-----------+------------------------+
 * | version   | length    | बारtamp | text                   |
 * | (2 bytes) | (2 bytes) | (8 bytes) | (oops_data_sz bytes)   |
 * +-----------+-----------+-----------+------------------------+
 * ^
 * +- oops_log_info
 *
 * We pपुनः_स्मृतिate these buffers during init to aव्योम kदो_स्मृति during oops/panic.
 */
अटल माप_प्रकार big_oops_buf_sz;
अटल अक्षर *big_oops_buf, *oops_buf;
अटल अक्षर *oops_data;
अटल माप_प्रकार oops_data_sz;

/* Compression parameters */
#घोषणा COMPR_LEVEL 6
#घोषणा WINDOW_BITS 12
#घोषणा MEM_LEVEL 4
अटल काष्ठा z_stream_s stream;

#अगर_घोषित CONFIG_PSTORE
#अगर_घोषित CONFIG_PPC_POWERNV
अटल काष्ठा nvram_os_partition skiboot_partition = अणु
	.name = "ibm,skiboot",
	.index = -1,
	.os_partition = false
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
अटल काष्ठा nvram_os_partition of_config_partition = अणु
	.name = "of-config",
	.index = -1,
	.os_partition = false
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा nvram_os_partition common_partition = अणु
	.name = "common",
	.index = -1,
	.os_partition = false
पूर्ण;

अटल क्रमागत pstore_type_id nvram_type_ids[] = अणु
	PSTORE_TYPE_DMESG,
	PSTORE_TYPE_PPC_COMMON,
	-1,
	-1,
	-1
पूर्ण;
अटल पूर्णांक पढ़ो_type;
#पूर्ण_अगर

/* nvram_ग_लिखो_os_partition
 *
 * We need to buffer the error logs पूर्णांकo nvram to ensure that we have
 * the failure inक्रमmation to decode.  If we have a severe error there
 * is no way to guarantee that the OS or the machine is in a state to
 * get back to user land and ग_लिखो the error to disk.  For example अगर
 * the SCSI device driver causes a Machine Check by writing to a bad
 * IO address, there is no way of guaranteeing that the device driver
 * is in any state that is would also be able to ग_लिखो the error data
 * captured to disk, thus we buffer it in NVRAM क्रम analysis on the
 * next boot.
 *
 * In NVRAM the partition containing the error log buffer will looks like:
 * Header (in bytes):
 * +-----------+----------+--------+------------+------------------+
 * | signature | checksum | length | name       | data             |
 * |0          |1         |2      3|4         15|16        length-1|
 * +-----------+----------+--------+------------+------------------+
 *
 * The 'data' section would look like (in bytes):
 * +--------------+------------+-----------------------------------+
 * | event_logged | sequence # | error log                         |
 * |0            3|4          7|8                  error_log_size-1|
 * +--------------+------------+-----------------------------------+
 *
 * event_logged: 0 अगर event has not been logged to syslog, 1 अगर it has
 * sequence #: The unique sequence # क्रम each event. (until it wraps)
 * error log: The error log from event_scan
 */
पूर्णांक nvram_ग_लिखो_os_partition(काष्ठा nvram_os_partition *part,
			     अक्षर *buff, पूर्णांक length,
			     अचिन्हित पूर्णांक err_type,
			     अचिन्हित पूर्णांक error_log_cnt)
अणु
	पूर्णांक rc;
	loff_t पंचांगp_index;
	काष्ठा err_log_info info;

	अगर (part->index == -1)
		वापस -ESPIPE;

	अगर (length > part->size)
		length = part->size;

	info.error_type = cpu_to_be32(err_type);
	info.seq_num = cpu_to_be32(error_log_cnt);

	पंचांगp_index = part->index;

	rc = ppc_md.nvram_ग_लिखो((अक्षर *)&info, माप(info), &पंचांगp_index);
	अगर (rc <= 0) अणु
		pr_err("%s: Failed nvram_write (%d)\n", __func__, rc);
		वापस rc;
	पूर्ण

	rc = ppc_md.nvram_ग_लिखो(buff, length, &पंचांगp_index);
	अगर (rc <= 0) अणु
		pr_err("%s: Failed nvram_write (%d)\n", __func__, rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/* nvram_पढ़ो_partition
 *
 * Reads nvram partition क्रम at most 'length'
 */
पूर्णांक nvram_पढ़ो_partition(काष्ठा nvram_os_partition *part, अक्षर *buff,
			 पूर्णांक length, अचिन्हित पूर्णांक *err_type,
			 अचिन्हित पूर्णांक *error_log_cnt)
अणु
	पूर्णांक rc;
	loff_t पंचांगp_index;
	काष्ठा err_log_info info;

	अगर (part->index == -1)
		वापस -1;

	अगर (length > part->size)
		length = part->size;

	पंचांगp_index = part->index;

	अगर (part->os_partition) अणु
		rc = ppc_md.nvram_पढ़ो((अक्षर *)&info, माप(info), &पंचांगp_index);
		अगर (rc <= 0) अणु
			pr_err("%s: Failed nvram_read (%d)\n", __func__, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = ppc_md.nvram_पढ़ो(buff, length, &पंचांगp_index);
	अगर (rc <= 0) अणु
		pr_err("%s: Failed nvram_read (%d)\n", __func__, rc);
		वापस rc;
	पूर्ण

	अगर (part->os_partition) अणु
		*error_log_cnt = be32_to_cpu(info.seq_num);
		*err_type = be32_to_cpu(info.error_type);
	पूर्ण

	वापस 0;
पूर्ण

/* nvram_init_os_partition
 *
 * This sets up a partition with an "OS" signature.
 *
 * The general strategy is the following:
 * 1.) If a partition with the indicated name alपढ़ोy exists...
 *	- If it's large enough, use it.
 *	- Otherwise, recycle it and keep going.
 * 2.) Search क्रम a मुक्त partition that is large enough.
 * 3.) If there's not a मुक्त partition large enough, recycle any obsolete
 * OS partitions and try again.
 * 4.) Will first try getting a chunk that will satisfy the requested size.
 * 5.) If a chunk of the requested size cannot be allocated, then try finding
 * a chunk that will satisfy the minum needed.
 *
 * Returns 0 on success, अन्यथा -1.
 */
पूर्णांक __init nvram_init_os_partition(काष्ठा nvram_os_partition *part)
अणु
	loff_t p;
	पूर्णांक size;

	/* Look क्रम ours */
	p = nvram_find_partition(part->name, NVRAM_SIG_OS, &size);

	/* Found one but too small, हटाओ it */
	अगर (p && size < part->min_size) अणु
		pr_info("nvram: Found too small %s partition,"
					" removing it...\n", part->name);
		nvram_हटाओ_partition(part->name, NVRAM_SIG_OS, शून्य);
		p = 0;
	पूर्ण

	/* Create one अगर we didn't find */
	अगर (!p) अणु
		p = nvram_create_partition(part->name, NVRAM_SIG_OS,
					part->req_size, part->min_size);
		अगर (p == -ENOSPC) अणु
			pr_info("nvram: No room to create %s partition, "
				"deleting any obsolete OS partitions...\n",
				part->name);
			nvram_हटाओ_partition(शून्य, NVRAM_SIG_OS,
					nvram_os_partitions);
			p = nvram_create_partition(part->name, NVRAM_SIG_OS,
					part->req_size, part->min_size);
		पूर्ण
	पूर्ण

	अगर (p <= 0) अणु
		pr_err("nvram: Failed to find or create %s"
		       " partition, err %d\n", part->name, (पूर्णांक)p);
		वापस -1;
	पूर्ण

	part->index = p;
	part->size = nvram_get_partition_size(p) - माप(काष्ठा err_log_info);

	वापस 0;
पूर्ण

/* Derived from logfs_compress() */
अटल पूर्णांक nvram_compress(स्थिर व्योम *in, व्योम *out, माप_प्रकार inlen,
							माप_प्रकार outlen)
अणु
	पूर्णांक err, ret;

	ret = -EIO;
	err = zlib_deflateInit2(&stream, COMPR_LEVEL, Z_DEFLATED, WINDOW_BITS,
						MEM_LEVEL, Z_DEFAULT_STRATEGY);
	अगर (err != Z_OK)
		जाओ error;

	stream.next_in = in;
	stream.avail_in = inlen;
	stream.total_in = 0;
	stream.next_out = out;
	stream.avail_out = outlen;
	stream.total_out = 0;

	err = zlib_deflate(&stream, Z_FINISH);
	अगर (err != Z_STREAM_END)
		जाओ error;

	err = zlib_deflateEnd(&stream);
	अगर (err != Z_OK)
		जाओ error;

	अगर (stream.total_out >= stream.total_in)
		जाओ error;

	ret = stream.total_out;
error:
	वापस ret;
पूर्ण

/* Compress the text from big_oops_buf पूर्णांकo oops_buf. */
अटल पूर्णांक zip_oops(माप_प्रकार text_len)
अणु
	काष्ठा oops_log_info *oops_hdr = (काष्ठा oops_log_info *)oops_buf;
	पूर्णांक zipped_len = nvram_compress(big_oops_buf, oops_data, text_len,
								oops_data_sz);
	अगर (zipped_len < 0) अणु
		pr_err("nvram: compression failed; returned %d\n", zipped_len);
		pr_err("nvram: logging uncompressed oops/panic report\n");
		वापस -1;
	पूर्ण
	oops_hdr->version = cpu_to_be16(OOPS_HDR_VERSION);
	oops_hdr->report_length = cpu_to_be16(zipped_len);
	oops_hdr->बारtamp = cpu_to_be64(kसमय_get_real_seconds());
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PSTORE
अटल पूर्णांक nvram_pstore_खोलो(काष्ठा pstore_info *psi)
अणु
	/* Reset the iterator to start पढ़ोing partitions again */
	पढ़ो_type = -1;
	वापस 0;
पूर्ण

/**
 * nvram_pstore_ग_लिखो - pstore ग_लिखो callback क्रम nvram
 * @record:             pstore record to ग_लिखो, with @id to be set
 *
 * Called by pstore_dump() when an oops or panic report is logged in the
 * prपूर्णांकk buffer.
 * Returns 0 on successful ग_लिखो.
 */
अटल पूर्णांक nvram_pstore_ग_लिखो(काष्ठा pstore_record *record)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक err_type = ERR_TYPE_KERNEL_PANIC;
	काष्ठा oops_log_info *oops_hdr = (काष्ठा oops_log_info *) oops_buf;

	/* part 1 has the recent messages from prपूर्णांकk buffer */
	अगर (record->part > 1 || (record->type != PSTORE_TYPE_DMESG))
		वापस -1;

	अगर (clobbering_unपढ़ो_rtas_event())
		वापस -1;

	oops_hdr->version = cpu_to_be16(OOPS_HDR_VERSION);
	oops_hdr->report_length = cpu_to_be16(record->size);
	oops_hdr->बारtamp = cpu_to_be64(kसमय_get_real_seconds());

	अगर (record->compressed)
		err_type = ERR_TYPE_KERNEL_PANIC_GZ;

	rc = nvram_ग_लिखो_os_partition(&oops_log_partition, oops_buf,
		(पूर्णांक) (माप(*oops_hdr) + record->size), err_type,
		record->count);

	अगर (rc != 0)
		वापस rc;

	record->id = record->part;
	वापस 0;
पूर्ण

/*
 * Reads the oops/panic report, rtas, of-config and common partition.
 * Returns the length of the data we पढ़ो from each partition.
 * Returns 0 अगर we've been called beक्रमe.
 */
अटल sमाप_प्रकार nvram_pstore_पढ़ो(काष्ठा pstore_record *record)
अणु
	काष्ठा oops_log_info *oops_hdr;
	अचिन्हित पूर्णांक err_type, id_no, size = 0;
	काष्ठा nvram_os_partition *part = शून्य;
	अक्षर *buff = शून्य;
	पूर्णांक sig = 0;
	loff_t p;

	पढ़ो_type++;

	चयन (nvram_type_ids[पढ़ो_type]) अणु
	हाल PSTORE_TYPE_DMESG:
		part = &oops_log_partition;
		record->type = PSTORE_TYPE_DMESG;
		अवरोध;
	हाल PSTORE_TYPE_PPC_COMMON:
		sig = NVRAM_SIG_SYS;
		part = &common_partition;
		record->type = PSTORE_TYPE_PPC_COMMON;
		record->id = PSTORE_TYPE_PPC_COMMON;
		record->समय.tv_sec = 0;
		record->समय.tv_nsec = 0;
		अवरोध;
#अगर_घोषित CONFIG_PPC_PSERIES
	हाल PSTORE_TYPE_PPC_RTAS:
		part = &rtas_log_partition;
		record->type = PSTORE_TYPE_PPC_RTAS;
		record->समय.tv_sec = last_rtas_event;
		record->समय.tv_nsec = 0;
		अवरोध;
	हाल PSTORE_TYPE_PPC_OF:
		sig = NVRAM_SIG_OF;
		part = &of_config_partition;
		record->type = PSTORE_TYPE_PPC_OF;
		record->id = PSTORE_TYPE_PPC_OF;
		record->समय.tv_sec = 0;
		record->समय.tv_nsec = 0;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_POWERNV
	हाल PSTORE_TYPE_PPC_OPAL:
		sig = NVRAM_SIG_FW;
		part = &skiboot_partition;
		record->type = PSTORE_TYPE_PPC_OPAL;
		record->id = PSTORE_TYPE_PPC_OPAL;
		record->समय.tv_sec = 0;
		record->समय.tv_nsec = 0;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस 0;
	पूर्ण

	अगर (!part->os_partition) अणु
		p = nvram_find_partition(part->name, sig, &size);
		अगर (p <= 0) अणु
			pr_err("nvram: Failed to find partition %s, "
				"err %d\n", part->name, (पूर्णांक)p);
			वापस 0;
		पूर्ण
		part->index = p;
		part->size = size;
	पूर्ण

	buff = kदो_स्मृति(part->size, GFP_KERNEL);

	अगर (!buff)
		वापस -ENOMEM;

	अगर (nvram_पढ़ो_partition(part, buff, part->size, &err_type, &id_no)) अणु
		kमुक्त(buff);
		वापस 0;
	पूर्ण

	record->count = 0;

	अगर (part->os_partition)
		record->id = id_no;

	अगर (nvram_type_ids[पढ़ो_type] == PSTORE_TYPE_DMESG) अणु
		माप_प्रकार length, hdr_size;

		oops_hdr = (काष्ठा oops_log_info *)buff;
		अगर (be16_to_cpu(oops_hdr->version) < OOPS_HDR_VERSION) अणु
			/* Old क्रमmat oops header had 2-byte record size */
			hdr_size = माप(u16);
			length = be16_to_cpu(oops_hdr->version);
			record->समय.tv_sec = 0;
			record->समय.tv_nsec = 0;
		पूर्ण अन्यथा अणु
			hdr_size = माप(*oops_hdr);
			length = be16_to_cpu(oops_hdr->report_length);
			record->समय.tv_sec = be64_to_cpu(oops_hdr->बारtamp);
			record->समय.tv_nsec = 0;
		पूर्ण
		record->buf = kmemdup(buff + hdr_size, length, GFP_KERNEL);
		kमुक्त(buff);
		अगर (record->buf == शून्य)
			वापस -ENOMEM;

		record->ecc_notice_size = 0;
		अगर (err_type == ERR_TYPE_KERNEL_PANIC_GZ)
			record->compressed = true;
		अन्यथा
			record->compressed = false;
		वापस length;
	पूर्ण

	record->buf = buff;
	वापस part->size;
पूर्ण

अटल काष्ठा pstore_info nvram_pstore_info = अणु
	.owner = THIS_MODULE,
	.name = "nvram",
	.flags = PSTORE_FLAGS_DMESG,
	.खोलो = nvram_pstore_खोलो,
	.पढ़ो = nvram_pstore_पढ़ो,
	.ग_लिखो = nvram_pstore_ग_लिखो,
पूर्ण;

अटल पूर्णांक nvram_pstore_init(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (machine_is(pseries)) अणु
		nvram_type_ids[2] = PSTORE_TYPE_PPC_RTAS;
		nvram_type_ids[3] = PSTORE_TYPE_PPC_OF;
	पूर्ण अन्यथा
		nvram_type_ids[2] = PSTORE_TYPE_PPC_OPAL;

	nvram_pstore_info.buf = oops_data;
	nvram_pstore_info.bufsize = oops_data_sz;

	rc = pstore_रेजिस्टर(&nvram_pstore_info);
	अगर (rc && (rc != -EPERM))
		/* Prपूर्णांक error only when pstore.backend == nvram */
		pr_err("nvram: pstore_register() failed, returned %d. "
				"Defaults to kmsg_dump\n", rc);

	वापस rc;
पूर्ण
#अन्यथा
अटल पूर्णांक nvram_pstore_init(व्योम)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

व्योम __init nvram_init_oops_partition(पूर्णांक rtas_partition_exists)
अणु
	पूर्णांक rc;

	rc = nvram_init_os_partition(&oops_log_partition);
	अगर (rc != 0) अणु
#अगर_घोषित CONFIG_PPC_PSERIES
		अगर (!rtas_partition_exists) अणु
			pr_err("nvram: Failed to initialize oops partition!");
			वापस;
		पूर्ण
		pr_notice("nvram: Using %s partition to log both"
			" RTAS errors and oops/panic reports\n",
			rtas_log_partition.name);
		स_नकल(&oops_log_partition, &rtas_log_partition,
						माप(rtas_log_partition));
#अन्यथा
		pr_err("nvram: Failed to initialize oops partition!");
		वापस;
#पूर्ण_अगर
	पूर्ण
	oops_buf = kदो_स्मृति(oops_log_partition.size, GFP_KERNEL);
	अगर (!oops_buf) अणु
		pr_err("nvram: No memory for %s partition\n",
						oops_log_partition.name);
		वापस;
	पूर्ण
	oops_data = oops_buf + माप(काष्ठा oops_log_info);
	oops_data_sz = oops_log_partition.size - माप(काष्ठा oops_log_info);

	rc = nvram_pstore_init();

	अगर (!rc)
		वापस;

	/*
	 * Figure compression (preceded by elimination of each line's <n>
	 * severity prefix) will reduce the oops/panic report to at most
	 * 45% of its original size.
	 */
	big_oops_buf_sz = (oops_data_sz * 100) / 45;
	big_oops_buf = kदो_स्मृति(big_oops_buf_sz, GFP_KERNEL);
	अगर (big_oops_buf) अणु
		stream.workspace =  kदो_स्मृति(zlib_deflate_workspacesize(
					WINDOW_BITS, MEM_LEVEL), GFP_KERNEL);
		अगर (!stream.workspace) अणु
			pr_err("nvram: No memory for compression workspace; "
				"skipping compression of %s partition data\n",
				oops_log_partition.name);
			kमुक्त(big_oops_buf);
			big_oops_buf = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("No memory for uncompressed %s data; "
			"skipping compression\n", oops_log_partition.name);
		stream.workspace = शून्य;
	पूर्ण

	rc = kmsg_dump_रेजिस्टर(&nvram_kmsg_dumper);
	अगर (rc != 0) अणु
		pr_err("nvram: kmsg_dump_register() failed; returned %d\n", rc);
		kमुक्त(oops_buf);
		kमुक्त(big_oops_buf);
		kमुक्त(stream.workspace);
	पूर्ण
पूर्ण

/*
 * This is our kmsg_dump callback, called after an oops or panic report
 * has been written to the prपूर्णांकk buffer.  We want to capture as much
 * of the prपूर्णांकk buffer as possible.  First, capture as much as we can
 * that we think will compress sufficiently to fit in the lnx,oops-log
 * partition.  If that's too much, go back and capture uncompressed text.
 */
अटल व्योम oops_to_nvram(काष्ठा kmsg_dumper *dumper,
			  क्रमागत kmsg_dump_reason reason)
अणु
	काष्ठा oops_log_info *oops_hdr = (काष्ठा oops_log_info *)oops_buf;
	अटल अचिन्हित पूर्णांक oops_count = 0;
	अटल काष्ठा kmsg_dump_iter iter;
	अटल bool panicking = false;
	अटल DEFINE_SPINLOCK(lock);
	अचिन्हित दीर्घ flags;
	माप_प्रकार text_len;
	अचिन्हित पूर्णांक err_type = ERR_TYPE_KERNEL_PANIC_GZ;
	पूर्णांक rc = -1;

	चयन (reason) अणु
	हाल KMSG_DUMP_SHUTDOWN:
		/* These are almost always orderly shutकरोwns. */
		वापस;
	हाल KMSG_DUMP_OOPS:
		अवरोध;
	हाल KMSG_DUMP_PANIC:
		panicking = true;
		अवरोध;
	हाल KMSG_DUMP_EMERG:
		अगर (panicking)
			/* Panic report alपढ़ोy captured. */
			वापस;
		अवरोध;
	शेष:
		pr_err("%s: ignoring unrecognized KMSG_DUMP_* reason %d\n",
		       __func__, (पूर्णांक) reason);
		वापस;
	पूर्ण

	अगर (clobbering_unपढ़ो_rtas_event())
		वापस;

	अगर (!spin_trylock_irqsave(&lock, flags))
		वापस;

	अगर (big_oops_buf) अणु
		kmsg_dump_शुरुआत(&iter);
		kmsg_dump_get_buffer(&iter, false,
				     big_oops_buf, big_oops_buf_sz, &text_len);
		rc = zip_oops(text_len);
	पूर्ण
	अगर (rc != 0) अणु
		kmsg_dump_शुरुआत(&iter);
		kmsg_dump_get_buffer(&iter, false,
				     oops_data, oops_data_sz, &text_len);
		err_type = ERR_TYPE_KERNEL_PANIC;
		oops_hdr->version = cpu_to_be16(OOPS_HDR_VERSION);
		oops_hdr->report_length = cpu_to_be16(text_len);
		oops_hdr->बारtamp = cpu_to_be64(kसमय_get_real_seconds());
	पूर्ण

	(व्योम) nvram_ग_लिखो_os_partition(&oops_log_partition, oops_buf,
		(पूर्णांक) (माप(*oops_hdr) + text_len), err_type,
		++oops_count);

	spin_unlock_irqrestore(&lock, flags);
पूर्ण

#अगर_घोषित DEBUG_NVRAM
अटल व्योम __init nvram_prपूर्णांक_partitions(अक्षर * label)
अणु
	काष्ठा nvram_partition * पंचांगp_part;
	
	prपूर्णांकk(KERN_WARNING "--------%s---------\n", label);
	prपूर्णांकk(KERN_WARNING "indx\t\tsig\tchks\tlen\tname\n");
	list_क्रम_each_entry(पंचांगp_part, &nvram_partitions, partition) अणु
		prपूर्णांकk(KERN_WARNING "%4d    \t%02x\t%02x\t%d\t%12.12s\n",
		       पंचांगp_part->index, पंचांगp_part->header.signature,
		       पंचांगp_part->header.checksum, पंचांगp_part->header.length,
		       पंचांगp_part->header.name);
	पूर्ण
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक __init nvram_ग_लिखो_header(काष्ठा nvram_partition * part)
अणु
	loff_t पंचांगp_index;
	पूर्णांक rc;
	काष्ठा nvram_header phead;

	स_नकल(&phead, &part->header, NVRAM_HEADER_LEN);
	phead.length = cpu_to_be16(phead.length);

	पंचांगp_index = part->index;
	rc = ppc_md.nvram_ग_लिखो((अक्षर *)&phead, NVRAM_HEADER_LEN, &पंचांगp_index);

	वापस rc;
पूर्ण


अटल अचिन्हित अक्षर __init nvram_checksum(काष्ठा nvram_header *p)
अणु
	अचिन्हित पूर्णांक c_sum, c_sum2;
	अचिन्हित लघु *sp = (अचिन्हित लघु *)p->name; /* assume 6 लघुs */
	c_sum = p->signature + p->length + sp[0] + sp[1] + sp[2] + sp[3] + sp[4] + sp[5];

	/* The sum may have spilled पूर्णांकo the 3rd byte.  Fold it back. */
	c_sum = ((c_sum & 0xffff) + (c_sum >> 16)) & 0xffff;
	/* The sum cannot exceed 2 bytes.  Fold it पूर्णांकo a checksum */
	c_sum2 = (c_sum >> 8) + (c_sum << 8);
	c_sum = ((c_sum + c_sum2) >> 8) & 0xff;
	वापस c_sum;
पूर्ण

/*
 * Per the criteria passed via nvram_हटाओ_partition(), should this
 * partition be हटाओd?  1=हटाओ, 0=keep
 */
अटल पूर्णांक nvram_can_हटाओ_partition(काष्ठा nvram_partition *part,
		स्थिर अक्षर *name, पूर्णांक sig, स्थिर अक्षर *exceptions[])
अणु
	अगर (part->header.signature != sig)
		वापस 0;
	अगर (name) अणु
		अगर (म_भेदन(name, part->header.name, 12))
			वापस 0;
	पूर्ण अन्यथा अगर (exceptions) अणु
		स्थिर अक्षर **except;
		क्रम (except = exceptions; *except; except++) अणु
			अगर (!म_भेदन(*except, part->header.name, 12))
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/**
 * nvram_हटाओ_partition - Remove one or more partitions in nvram
 * @name: name of the partition to हटाओ, or शून्य क्रम a
 *        signature only match
 * @sig: signature of the partition(s) to हटाओ
 * @exceptions: When removing all partitions with a matching signature,
 *        leave these alone.
 */

पूर्णांक __init nvram_हटाओ_partition(स्थिर अक्षर *name, पूर्णांक sig,
						स्थिर अक्षर *exceptions[])
अणु
	काष्ठा nvram_partition *part, *prev, *पंचांगp;
	पूर्णांक rc;

	list_क्रम_each_entry(part, &nvram_partitions, partition) अणु
		अगर (!nvram_can_हटाओ_partition(part, name, sig, exceptions))
			जारी;

		/* Make partition a मुक्त partition */
		part->header.signature = NVRAM_SIG_FREE;
		स_रखो(part->header.name, 'w', 12);
		part->header.checksum = nvram_checksum(&part->header);
		rc = nvram_ग_लिखो_header(part);
		अगर (rc <= 0) अणु
			prपूर्णांकk(KERN_ERR "nvram_remove_partition: nvram_write failed (%d)\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Merge contiguous ones */
	prev = शून्य;
	list_क्रम_each_entry_safe(part, पंचांगp, &nvram_partitions, partition) अणु
		अगर (part->header.signature != NVRAM_SIG_FREE) अणु
			prev = शून्य;
			जारी;
		पूर्ण
		अगर (prev) अणु
			prev->header.length += part->header.length;
			prev->header.checksum = nvram_checksum(&prev->header);
			rc = nvram_ग_लिखो_header(prev);
			अगर (rc <= 0) अणु
				prपूर्णांकk(KERN_ERR "nvram_remove_partition: nvram_write failed (%d)\n", rc);
				वापस rc;
			पूर्ण
			list_del(&part->partition);
			kमुक्त(part);
		पूर्ण अन्यथा
			prev = part;
	पूर्ण
	
	वापस 0;
पूर्ण

/**
 * nvram_create_partition - Create a partition in nvram
 * @name: name of the partition to create
 * @sig: signature of the partition to create
 * @req_size: size of data to allocate in bytes
 * @min_size: minimum acceptable size (0 means req_size)
 *
 * Returns a negative error code or a positive nvram index
 * of the beginning of the data area of the newly created
 * partition. If you provided a min_size smaller than req_size
 * you need to query क्रम the actual size yourself after the
 * call using nvram_partition_get_size().
 */
loff_t __init nvram_create_partition(स्थिर अक्षर *name, पूर्णांक sig,
				     पूर्णांक req_size, पूर्णांक min_size)
अणु
	काष्ठा nvram_partition *part;
	काष्ठा nvram_partition *new_part;
	काष्ठा nvram_partition *मुक्त_part = शून्य;
	अटल अक्षर nv_init_vals[16];
	loff_t पंचांगp_index;
	दीर्घ size = 0;
	पूर्णांक rc;

	BUILD_BUG_ON(NVRAM_BLOCK_LEN != 16);

	/* Convert sizes from bytes to blocks */
	req_size = ALIGN(req_size, NVRAM_BLOCK_LEN) / NVRAM_BLOCK_LEN;
	min_size = ALIGN(min_size, NVRAM_BLOCK_LEN) / NVRAM_BLOCK_LEN;

	/* If no minimum size specअगरied, make it the same as the
	 * requested size
	 */
	अगर (min_size == 0)
		min_size = req_size;
	अगर (min_size > req_size)
		वापस -EINVAL;

	/* Now add one block to each क्रम the header */
	req_size += 1;
	min_size += 1;

	/* Find a मुक्त partition that will give us the maximum needed size 
	   If can't find one that will give us the minimum size needed */
	list_क्रम_each_entry(part, &nvram_partitions, partition) अणु
		अगर (part->header.signature != NVRAM_SIG_FREE)
			जारी;

		अगर (part->header.length >= req_size) अणु
			size = req_size;
			मुक्त_part = part;
			अवरोध;
		पूर्ण
		अगर (part->header.length > size &&
		    part->header.length >= min_size) अणु
			size = part->header.length;
			मुक्त_part = part;
		पूर्ण
	पूर्ण
	अगर (!size)
		वापस -ENOSPC;
	
	/* Create our OS partition */
	new_part = kzalloc(माप(*new_part), GFP_KERNEL);
	अगर (!new_part) अणु
		pr_err("%s: kmalloc failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	new_part->index = मुक्त_part->index;
	new_part->header.signature = sig;
	new_part->header.length = size;
	स_नकल(new_part->header.name, name, strnlen(name, माप(new_part->header.name)));
	new_part->header.checksum = nvram_checksum(&new_part->header);

	rc = nvram_ग_लिखो_header(new_part);
	अगर (rc <= 0) अणु
		pr_err("%s: nvram_write_header failed (%d)\n", __func__, rc);
		kमुक्त(new_part);
		वापस rc;
	पूर्ण
	list_add_tail(&new_part->partition, &मुक्त_part->partition);

	/* Adjust or हटाओ the partition we stole the space from */
	अगर (मुक्त_part->header.length > size) अणु
		मुक्त_part->index += size * NVRAM_BLOCK_LEN;
		मुक्त_part->header.length -= size;
		मुक्त_part->header.checksum = nvram_checksum(&मुक्त_part->header);
		rc = nvram_ग_लिखो_header(मुक्त_part);
		अगर (rc <= 0) अणु
			pr_err("%s: nvram_write_header failed (%d)\n",
			       __func__, rc);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_del(&मुक्त_part->partition);
		kमुक्त(मुक्त_part);
	पूर्ण 

	/* Clear the new partition */
	क्रम (पंचांगp_index = new_part->index + NVRAM_HEADER_LEN;
	     पंचांगp_index <  ((size - 1) * NVRAM_BLOCK_LEN);
	     पंचांगp_index += NVRAM_BLOCK_LEN) अणु
		rc = ppc_md.nvram_ग_लिखो(nv_init_vals, NVRAM_BLOCK_LEN, &पंचांगp_index);
		अगर (rc <= 0) अणु
			pr_err("%s: nvram_write failed (%d)\n",
			       __func__, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस new_part->index + NVRAM_HEADER_LEN;
पूर्ण

/**
 * nvram_get_partition_size - Get the data size of an nvram partition
 * @data_index: This is the offset of the start of the data of
 *              the partition. The same value that is वापसed by
 *              nvram_create_partition().
 */
पूर्णांक nvram_get_partition_size(loff_t data_index)
अणु
	काष्ठा nvram_partition *part;
	
	list_क्रम_each_entry(part, &nvram_partitions, partition) अणु
		अगर (part->index + NVRAM_HEADER_LEN == data_index)
			वापस (part->header.length - 1) * NVRAM_BLOCK_LEN;
	पूर्ण
	वापस -1;
पूर्ण


/**
 * nvram_find_partition - Find an nvram partition by signature and name
 * @name: Name of the partition or शून्य क्रम any name
 * @sig: Signature to test against
 * @out_size: अगर non-शून्य, वापसs the size of the data part of the partition
 */
loff_t nvram_find_partition(स्थिर अक्षर *name, पूर्णांक sig, पूर्णांक *out_size)
अणु
	काष्ठा nvram_partition *p;

	list_क्रम_each_entry(p, &nvram_partitions, partition) अणु
		अगर (p->header.signature == sig &&
		    (!name || !म_भेदन(p->header.name, name, 12))) अणु
			अगर (out_size)
				*out_size = (p->header.length - 1) *
					NVRAM_BLOCK_LEN;
			वापस p->index + NVRAM_HEADER_LEN;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init nvram_scan_partitions(व्योम)
अणु
	loff_t cur_index = 0;
	काष्ठा nvram_header phead;
	काष्ठा nvram_partition * पंचांगp_part;
	अचिन्हित अक्षर c_sum;
	अक्षर * header;
	पूर्णांक total_size;
	पूर्णांक err;

	अगर (ppc_md.nvram_size == शून्य || ppc_md.nvram_size() <= 0)
		वापस -ENODEV;
	total_size = ppc_md.nvram_size();
	
	header = kदो_स्मृति(NVRAM_HEADER_LEN, GFP_KERNEL);
	अगर (!header) अणु
		prपूर्णांकk(KERN_ERR "nvram_scan_partitions: Failed kmalloc\n");
		वापस -ENOMEM;
	पूर्ण

	जबतक (cur_index < total_size) अणु

		err = ppc_md.nvram_पढ़ो(header, NVRAM_HEADER_LEN, &cur_index);
		अगर (err != NVRAM_HEADER_LEN) अणु
			prपूर्णांकk(KERN_ERR "nvram_scan_partitions: Error parsing "
			       "nvram partitions\n");
			जाओ out;
		पूर्ण

		cur_index -= NVRAM_HEADER_LEN; /* nvram_पढ़ो will advance us */

		स_नकल(&phead, header, NVRAM_HEADER_LEN);

		phead.length = be16_to_cpu(phead.length);

		err = 0;
		c_sum = nvram_checksum(&phead);
		अगर (c_sum != phead.checksum) अणु
			prपूर्णांकk(KERN_WARNING "WARNING: nvram partition checksum"
			       " was %02x, should be %02x!\n",
			       phead.checksum, c_sum);
			prपूर्णांकk(KERN_WARNING "Terminating nvram partition scan\n");
			जाओ out;
		पूर्ण
		अगर (!phead.length) अणु
			prपूर्णांकk(KERN_WARNING "WARNING: nvram corruption "
			       "detected: 0-length partition\n");
			जाओ out;
		पूर्ण
		पंचांगp_part = kदो_स्मृति(माप(*पंचांगp_part), GFP_KERNEL);
		err = -ENOMEM;
		अगर (!पंचांगp_part) अणु
			prपूर्णांकk(KERN_ERR "nvram_scan_partitions: kmalloc failed\n");
			जाओ out;
		पूर्ण
		
		स_नकल(&पंचांगp_part->header, &phead, NVRAM_HEADER_LEN);
		पंचांगp_part->index = cur_index;
		list_add_tail(&पंचांगp_part->partition, &nvram_partitions);
		
		cur_index += phead.length * NVRAM_BLOCK_LEN;
	पूर्ण
	err = 0;

#अगर_घोषित DEBUG_NVRAM
	nvram_prपूर्णांक_partitions("NVRAM Partitions");
#पूर्ण_अगर

 out:
	kमुक्त(header);
	वापस err;
पूर्ण
