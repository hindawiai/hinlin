<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Hypervisor fileप्रणाली क्रम Linux on s390. z/VM implementation.
 *
 *    Copyright IBM Corp. 2006
 *    Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/समयx.h>
#समावेश "hypfs.h"

#घोषणा NAME_LEN 8
#घोषणा DBFS_D2FC_HDR_VERSION 0

अटल अक्षर local_guest[] = "        ";
अटल अक्षर all_guests[] = "*       ";
अटल अक्षर *guest_query;

काष्ठा diag2fc_data अणु
	__u32 version;
	__u32 flags;
	__u64 used_cpu;
	__u64 el_समय;
	__u64 mem_min_kb;
	__u64 mem_max_kb;
	__u64 mem_share_kb;
	__u64 mem_used_kb;
	__u32 pcpus;
	__u32 lcpus;
	__u32 vcpus;
	__u32 ocpus;
	__u32 cpu_max;
	__u32 cpu_shares;
	__u32 cpu_use_samp;
	__u32 cpu_delay_samp;
	__u32 page_रुको_samp;
	__u32 idle_samp;
	__u32 other_samp;
	__u32 total_samp;
	अक्षर  guest_name[NAME_LEN];
पूर्ण;

काष्ठा diag2fc_parm_list अणु
	अक्षर userid[NAME_LEN];
	अक्षर aci_grp[NAME_LEN];
	__u64 addr;
	__u32 size;
	__u32 fmt;
पूर्ण;

अटल पूर्णांक diag2fc(पूर्णांक size, अक्षर* query, व्योम *addr)
अणु
	अचिन्हित दीर्घ residual_cnt;
	अचिन्हित दीर्घ rc;
	काष्ठा diag2fc_parm_list parm_list;

	स_नकल(parm_list.userid, query, NAME_LEN);
	ASCEBC(parm_list.userid, NAME_LEN);
	parm_list.addr = (अचिन्हित दीर्घ) addr ;
	parm_list.size = size;
	parm_list.fmt = 0x02;
	स_रखो(parm_list.aci_grp, 0x40, NAME_LEN);
	rc = -1;

	diag_stat_inc(DIAG_STAT_X2FC);
	यंत्र अस्थिर(
		"	diag    %0,%1,0x2fc\n"
		"0:	nopr	%%r7\n"
		EX_TABLE(0b,0b)
		: "=d" (residual_cnt), "+d" (rc) : "0" (&parm_list) : "memory");

	अगर ((rc != 0 ) && (rc != -2))
		वापस rc;
	अन्यथा
		वापस -residual_cnt;
पूर्ण

/*
 * Allocate buffer क्रम "query" and store diag 2fc at "offset"
 */
अटल व्योम *diag2fc_store(अक्षर *query, अचिन्हित पूर्णांक *count, पूर्णांक offset)
अणु
	व्योम *data;
	पूर्णांक size;

	करो अणु
		size = diag2fc(0, query, शून्य);
		अगर (size < 0)
			वापस ERR_PTR(-EACCES);
		data = vदो_स्मृति(size + offset);
		अगर (!data)
			वापस ERR_PTR(-ENOMEM);
		अगर (diag2fc(size, query, data + offset) == 0)
			अवरोध;
		vमुक्त(data);
	पूर्ण जबतक (1);
	*count = (size / माप(काष्ठा diag2fc_data));

	वापस data;
पूर्ण

अटल व्योम diag2fc_मुक्त(स्थिर व्योम *data)
अणु
	vमुक्त(data);
पूर्ण

#घोषणा ATTRIBUTE(dir, name, member) \
करो अणु \
	व्योम *rc; \
	rc = hypfs_create_u64(dir, name, member); \
	अगर (IS_ERR(rc)) \
		वापस PTR_ERR(rc); \
पूर्ण जबतक(0)

अटल पूर्णांक hypfs_vm_create_guest(काष्ठा dentry *प्रणालीs_dir,
				 काष्ठा diag2fc_data *data)
अणु
	अक्षर guest_name[NAME_LEN + 1] = अणुपूर्ण;
	काष्ठा dentry *guest_dir, *cpus_dir, *samples_dir, *mem_dir;
	पूर्णांक dedicated_flag, capped_value;

	capped_value = (data->flags & 0x00000006) >> 1;
	dedicated_flag = (data->flags & 0x00000008) >> 3;

	/* guest dir */
	स_नकल(guest_name, data->guest_name, NAME_LEN);
	EBCASC(guest_name, NAME_LEN);
	strim(guest_name);
	guest_dir = hypfs_सूची_गढ़ो(प्रणालीs_dir, guest_name);
	अगर (IS_ERR(guest_dir))
		वापस PTR_ERR(guest_dir);
	ATTRIBUTE(guest_dir, "onlinetime_us", data->el_समय);

	/* logical cpu inक्रमmation */
	cpus_dir = hypfs_सूची_गढ़ो(guest_dir, "cpus");
	अगर (IS_ERR(cpus_dir))
		वापस PTR_ERR(cpus_dir);
	ATTRIBUTE(cpus_dir, "cputime_us", data->used_cpu);
	ATTRIBUTE(cpus_dir, "capped", capped_value);
	ATTRIBUTE(cpus_dir, "dedicated", dedicated_flag);
	ATTRIBUTE(cpus_dir, "count", data->vcpus);
	/*
	 * Note: The "weight_min" attribute got the wrong name.
	 * The value represents the number of non-stopped (operating)
	 * CPUS.
	 */
	ATTRIBUTE(cpus_dir, "weight_min", data->ocpus);
	ATTRIBUTE(cpus_dir, "weight_max", data->cpu_max);
	ATTRIBUTE(cpus_dir, "weight_cur", data->cpu_shares);

	/* memory inक्रमmation */
	mem_dir = hypfs_सूची_गढ़ो(guest_dir, "mem");
	अगर (IS_ERR(mem_dir))
		वापस PTR_ERR(mem_dir);
	ATTRIBUTE(mem_dir, "min_KiB", data->mem_min_kb);
	ATTRIBUTE(mem_dir, "max_KiB", data->mem_max_kb);
	ATTRIBUTE(mem_dir, "used_KiB", data->mem_used_kb);
	ATTRIBUTE(mem_dir, "share_KiB", data->mem_share_kb);

	/* samples */
	samples_dir = hypfs_सूची_गढ़ो(guest_dir, "samples");
	अगर (IS_ERR(samples_dir))
		वापस PTR_ERR(samples_dir);
	ATTRIBUTE(samples_dir, "cpu_using", data->cpu_use_samp);
	ATTRIBUTE(samples_dir, "cpu_delay", data->cpu_delay_samp);
	ATTRIBUTE(samples_dir, "mem_delay", data->page_रुको_samp);
	ATTRIBUTE(samples_dir, "idle", data->idle_samp);
	ATTRIBUTE(samples_dir, "other", data->other_samp);
	ATTRIBUTE(samples_dir, "total", data->total_samp);
	वापस 0;
पूर्ण

पूर्णांक hypfs_vm_create_files(काष्ठा dentry *root)
अणु
	काष्ठा dentry *dir, *file;
	काष्ठा diag2fc_data *data;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक rc, i;

	data = diag2fc_store(guest_query, &count, 0);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/* Hpervisor Info */
	dir = hypfs_सूची_गढ़ो(root, "hyp");
	अगर (IS_ERR(dir)) अणु
		rc = PTR_ERR(dir);
		जाओ failed;
	पूर्ण
	file = hypfs_create_str(dir, "type", "z/VM Hypervisor");
	अगर (IS_ERR(file)) अणु
		rc = PTR_ERR(file);
		जाओ failed;
	पूर्ण

	/* physical cpus */
	dir = hypfs_सूची_गढ़ो(root, "cpus");
	अगर (IS_ERR(dir)) अणु
		rc = PTR_ERR(dir);
		जाओ failed;
	पूर्ण
	file = hypfs_create_u64(dir, "count", data->lcpus);
	अगर (IS_ERR(file)) अणु
		rc = PTR_ERR(file);
		जाओ failed;
	पूर्ण

	/* guests */
	dir = hypfs_सूची_गढ़ो(root, "systems");
	अगर (IS_ERR(dir)) अणु
		rc = PTR_ERR(dir);
		जाओ failed;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		rc = hypfs_vm_create_guest(dir, &(data[i]));
		अगर (rc)
			जाओ failed;
	पूर्ण
	diag2fc_मुक्त(data);
	वापस 0;

failed:
	diag2fc_मुक्त(data);
	वापस rc;
पूर्ण

काष्ठा dbfs_d2fc_hdr अणु
	u64	len;		/* Length of d2fc buffer without header */
	u16	version;	/* Version of header */
	जोड़ tod_घड़ी tod_ext; /* TOD घड़ी क्रम d2fc */
	u64	count;		/* Number of VM guests in d2fc buffer */
	अक्षर	reserved[30];
पूर्ण __attribute__ ((packed));

काष्ठा dbfs_d2fc अणु
	काष्ठा dbfs_d2fc_hdr	hdr;	/* 64 byte header */
	अक्षर			buf[];	/* d2fc buffer */
पूर्ण __attribute__ ((packed));

अटल पूर्णांक dbfs_diag2fc_create(व्योम **data, व्योम **data_मुक्त_ptr, माप_प्रकार *size)
अणु
	काष्ठा dbfs_d2fc *d2fc;
	अचिन्हित पूर्णांक count;

	d2fc = diag2fc_store(guest_query, &count, माप(d2fc->hdr));
	अगर (IS_ERR(d2fc))
		वापस PTR_ERR(d2fc);
	store_tod_घड़ी_ext(&d2fc->hdr.tod_ext);
	d2fc->hdr.len = count * माप(काष्ठा diag2fc_data);
	d2fc->hdr.version = DBFS_D2FC_HDR_VERSION;
	d2fc->hdr.count = count;
	स_रखो(&d2fc->hdr.reserved, 0, माप(d2fc->hdr.reserved));
	*data = d2fc;
	*data_मुक्त_ptr = d2fc;
	*size = d2fc->hdr.len + माप(काष्ठा dbfs_d2fc_hdr);
	वापस 0;
पूर्ण

अटल काष्ठा hypfs_dbfs_file dbfs_file_2fc = अणु
	.name		= "diag_2fc",
	.data_create	= dbfs_diag2fc_create,
	.data_मुक्त	= diag2fc_मुक्त,
पूर्ण;

पूर्णांक hypfs_vm_init(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 0;
	अगर (diag2fc(0, all_guests, शून्य) > 0)
		guest_query = all_guests;
	अन्यथा अगर (diag2fc(0, local_guest, शून्य) > 0)
		guest_query = local_guest;
	अन्यथा
		वापस -EACCES;
	hypfs_dbfs_create_file(&dbfs_file_2fc);
	वापस 0;
पूर्ण

व्योम hypfs_vm_निकास(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस;
	hypfs_dbfs_हटाओ_file(&dbfs_file_2fc);
पूर्ण
