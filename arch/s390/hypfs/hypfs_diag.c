<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Hypervisor fileप्रणाली क्रम Linux on s390. Diag 204 and 224
 *    implementation.
 *
 *    Copyright IBM Corp. 2006, 2008
 *    Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "hypfs"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश "hypfs.h"

#घोषणा TMP_SIZE 64		/* size of temporary buffers */

#घोषणा DBFS_D204_HDR_VERSION	0

अटल अक्षर *diag224_cpu_names;			/* diag 224 name table */
अटल क्रमागत diag204_sc diag204_store_sc;	/* used subcode क्रम store */
अटल क्रमागत diag204_क्रमmat diag204_info_type;	/* used diag 204 data क्रमmat */

अटल व्योम *diag204_buf;		/* 4K aligned buffer क्रम diag204 data */
अटल व्योम *diag204_buf_vदो_स्मृति;	/* vदो_स्मृति poपूर्णांकer क्रम diag204 data */
अटल पूर्णांक diag204_buf_pages;		/* number of pages क्रम diag204 data */

अटल काष्ठा dentry *dbfs_d204_file;

/*
 * DIAG 204 member access functions.
 *
 * Since we have two dअगरferent diag 204 data क्रमmats क्रम old and new s390
 * machines, we करो not access the काष्ठाs directly, but use getter functions क्रम
 * each काष्ठा member instead. This should make the code more पढ़ोable.
 */

/* Time inक्रमmation block */

अटल अंतरभूत पूर्णांक info_blk_hdr__size(क्रमागत diag204_क्रमmat type)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस माप(काष्ठा diag204_info_blk_hdr);
	अन्यथा /* DIAG204_INFO_EXT */
		वापस माप(काष्ठा diag204_x_info_blk_hdr);
पूर्ण

अटल अंतरभूत __u8 info_blk_hdr__npar(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_info_blk_hdr *)hdr)->npar;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_info_blk_hdr *)hdr)->npar;
पूर्ण

अटल अंतरभूत __u8 info_blk_hdr__flags(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_info_blk_hdr *)hdr)->flags;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_info_blk_hdr *)hdr)->flags;
पूर्ण

अटल अंतरभूत __u16 info_blk_hdr__pcpus(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_info_blk_hdr *)hdr)->phys_cpus;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_info_blk_hdr *)hdr)->phys_cpus;
पूर्ण

/* Partition header */

अटल अंतरभूत पूर्णांक part_hdr__size(क्रमागत diag204_क्रमmat type)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस माप(काष्ठा diag204_part_hdr);
	अन्यथा /* DIAG204_INFO_EXT */
		वापस माप(काष्ठा diag204_x_part_hdr);
पूर्ण

अटल अंतरभूत __u8 part_hdr__rcpus(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_part_hdr *)hdr)->cpus;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_part_hdr *)hdr)->rcpus;
पूर्ण

अटल अंतरभूत व्योम part_hdr__part_name(क्रमागत diag204_क्रमmat type, व्योम *hdr,
				       अक्षर *name)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		स_नकल(name, ((काष्ठा diag204_part_hdr *)hdr)->part_name,
		       DIAG204_LPAR_NAME_LEN);
	अन्यथा /* DIAG204_INFO_EXT */
		स_नकल(name, ((काष्ठा diag204_x_part_hdr *)hdr)->part_name,
		       DIAG204_LPAR_NAME_LEN);
	EBCASC(name, DIAG204_LPAR_NAME_LEN);
	name[DIAG204_LPAR_NAME_LEN] = 0;
	strim(name);
पूर्ण

/* CPU info block */

अटल अंतरभूत पूर्णांक cpu_info__size(क्रमागत diag204_क्रमmat type)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस माप(काष्ठा diag204_cpu_info);
	अन्यथा /* DIAG204_INFO_EXT */
		वापस माप(काष्ठा diag204_x_cpu_info);
पूर्ण

अटल अंतरभूत __u8 cpu_info__ctidx(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_cpu_info *)hdr)->ctidx;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_cpu_info *)hdr)->ctidx;
पूर्ण

अटल अंतरभूत __u16 cpu_info__cpu_addr(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_cpu_info *)hdr)->cpu_addr;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_cpu_info *)hdr)->cpu_addr;
पूर्ण

अटल अंतरभूत __u64 cpu_info__acc_समय(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_cpu_info *)hdr)->acc_समय;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_cpu_info *)hdr)->acc_समय;
पूर्ण

अटल अंतरभूत __u64 cpu_info__lp_समय(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_cpu_info *)hdr)->lp_समय;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_cpu_info *)hdr)->lp_समय;
पूर्ण

अटल अंतरभूत __u64 cpu_info__online_समय(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस 0;	/* online_समय not available in simple info */
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_cpu_info *)hdr)->online_समय;
पूर्ण

/* Physical header */

अटल अंतरभूत पूर्णांक phys_hdr__size(क्रमागत diag204_क्रमmat type)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस माप(काष्ठा diag204_phys_hdr);
	अन्यथा /* DIAG204_INFO_EXT */
		वापस माप(काष्ठा diag204_x_phys_hdr);
पूर्ण

अटल अंतरभूत __u8 phys_hdr__cpus(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_phys_hdr *)hdr)->cpus;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_phys_hdr *)hdr)->cpus;
पूर्ण

/* Physical CPU info block */

अटल अंतरभूत पूर्णांक phys_cpu__size(क्रमागत diag204_क्रमmat type)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस माप(काष्ठा diag204_phys_cpu);
	अन्यथा /* DIAG204_INFO_EXT */
		वापस माप(काष्ठा diag204_x_phys_cpu);
पूर्ण

अटल अंतरभूत __u16 phys_cpu__cpu_addr(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_phys_cpu *)hdr)->cpu_addr;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_phys_cpu *)hdr)->cpu_addr;
पूर्ण

अटल अंतरभूत __u64 phys_cpu__mgm_समय(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_phys_cpu *)hdr)->mgm_समय;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_phys_cpu *)hdr)->mgm_समय;
पूर्ण

अटल अंतरभूत __u64 phys_cpu__ctidx(क्रमागत diag204_क्रमmat type, व्योम *hdr)
अणु
	अगर (type == DIAG204_INFO_SIMPLE)
		वापस ((काष्ठा diag204_phys_cpu *)hdr)->ctidx;
	अन्यथा /* DIAG204_INFO_EXT */
		वापस ((काष्ठा diag204_x_phys_cpu *)hdr)->ctidx;
पूर्ण

/* Diagnose 204 functions */
/*
 * For the old diag subcode 4 with simple data क्रमmat we have to use real
 * memory. If we use subcode 6 or 7 with extended data क्रमmat, we can (and
 * should) use vदो_स्मृति, since we need a lot of memory in that हाल. Currently
 * up to 93 pages!
 */

अटल व्योम diag204_मुक्त_buffer(व्योम)
अणु
	अगर (!diag204_buf)
		वापस;
	अगर (diag204_buf_vदो_स्मृति) अणु
		vमुक्त(diag204_buf_vदो_स्मृति);
		diag204_buf_vदो_स्मृति = शून्य;
	पूर्ण अन्यथा अणु
		मुक्त_pages((अचिन्हित दीर्घ) diag204_buf, 0);
	पूर्ण
	diag204_buf = शून्य;
पूर्ण

अटल व्योम *page_align_ptr(व्योम *ptr)
अणु
	वापस (व्योम *) PAGE_ALIGN((अचिन्हित दीर्घ) ptr);
पूर्ण

अटल व्योम *diag204_alloc_vbuf(पूर्णांक pages)
अणु
	/* The buffer has to be page aligned! */
	diag204_buf_vदो_स्मृति = vदो_स्मृति(array_size(PAGE_SIZE, (pages + 1)));
	अगर (!diag204_buf_vदो_स्मृति)
		वापस ERR_PTR(-ENOMEM);
	diag204_buf = page_align_ptr(diag204_buf_vदो_स्मृति);
	diag204_buf_pages = pages;
	वापस diag204_buf;
पूर्ण

अटल व्योम *diag204_alloc_rbuf(व्योम)
अणु
	diag204_buf = (व्योम*)__get_मुक्त_pages(GFP_KERNEL,0);
	अगर (!diag204_buf)
		वापस ERR_PTR(-ENOMEM);
	diag204_buf_pages = 1;
	वापस diag204_buf;
पूर्ण

अटल व्योम *diag204_get_buffer(क्रमागत diag204_क्रमmat fmt, पूर्णांक *pages)
अणु
	अगर (diag204_buf) अणु
		*pages = diag204_buf_pages;
		वापस diag204_buf;
	पूर्ण
	अगर (fmt == DIAG204_INFO_SIMPLE) अणु
		*pages = 1;
		वापस diag204_alloc_rbuf();
	पूर्ण अन्यथा अणु/* DIAG204_INFO_EXT */
		*pages = diag204((अचिन्हित दीर्घ)DIAG204_SUBC_RSI |
				 (अचिन्हित दीर्घ)DIAG204_INFO_EXT, 0, शून्य);
		अगर (*pages <= 0)
			वापस ERR_PTR(-ENOSYS);
		अन्यथा
			वापस diag204_alloc_vbuf(*pages);
	पूर्ण
पूर्ण

/*
 * diag204_probe() has to find out, which type of diagnose 204 implementation
 * we have on our machine. Currently there are three possible scanarios:
 *   - subcode 4   + simple data क्रमmat (only one page)
 *   - subcode 4-6 + extended data क्रमmat
 *   - subcode 4-7 + extended data क्रमmat
 *
 * Subcode 5 is used to retrieve the size of the data, provided by subcodes
 * 6 and 7. Subcode 7 basically has the same function as subcode 6. In addition
 * to subcode 6 it provides also inक्रमmation about secondary cpus.
 * In order to get as much inक्रमmation as possible, we first try
 * subcode 7, then 6 and अगर both fail, we use subcode 4.
 */

अटल पूर्णांक diag204_probe(व्योम)
अणु
	व्योम *buf;
	पूर्णांक pages, rc;

	buf = diag204_get_buffer(DIAG204_INFO_EXT, &pages);
	अगर (!IS_ERR(buf)) अणु
		अगर (diag204((अचिन्हित दीर्घ)DIAG204_SUBC_STIB7 |
			    (अचिन्हित दीर्घ)DIAG204_INFO_EXT, pages, buf) >= 0) अणु
			diag204_store_sc = DIAG204_SUBC_STIB7;
			diag204_info_type = DIAG204_INFO_EXT;
			जाओ out;
		पूर्ण
		अगर (diag204((अचिन्हित दीर्घ)DIAG204_SUBC_STIB6 |
			    (अचिन्हित दीर्घ)DIAG204_INFO_EXT, pages, buf) >= 0) अणु
			diag204_store_sc = DIAG204_SUBC_STIB6;
			diag204_info_type = DIAG204_INFO_EXT;
			जाओ out;
		पूर्ण
		diag204_मुक्त_buffer();
	पूर्ण

	/* subcodes 6 and 7 failed, now try subcode 4 */

	buf = diag204_get_buffer(DIAG204_INFO_SIMPLE, &pages);
	अगर (IS_ERR(buf)) अणु
		rc = PTR_ERR(buf);
		जाओ fail_alloc;
	पूर्ण
	अगर (diag204((अचिन्हित दीर्घ)DIAG204_SUBC_STIB4 |
		    (अचिन्हित दीर्घ)DIAG204_INFO_SIMPLE, pages, buf) >= 0) अणु
		diag204_store_sc = DIAG204_SUBC_STIB4;
		diag204_info_type = DIAG204_INFO_SIMPLE;
		जाओ out;
	पूर्ण अन्यथा अणु
		rc = -ENOSYS;
		जाओ fail_store;
	पूर्ण
out:
	rc = 0;
fail_store:
	diag204_मुक्त_buffer();
fail_alloc:
	वापस rc;
पूर्ण

अटल पूर्णांक diag204_करो_store(व्योम *buf, पूर्णांक pages)
अणु
	पूर्णांक rc;

	rc = diag204((अचिन्हित दीर्घ) diag204_store_sc |
		     (अचिन्हित दीर्घ) diag204_info_type, pages, buf);
	वापस rc < 0 ? -ENOSYS : 0;
पूर्ण

अटल व्योम *diag204_store(व्योम)
अणु
	व्योम *buf;
	पूर्णांक pages, rc;

	buf = diag204_get_buffer(diag204_info_type, &pages);
	अगर (IS_ERR(buf))
		जाओ out;
	rc = diag204_करो_store(buf, pages);
	अगर (rc)
		वापस ERR_PTR(rc);
out:
	वापस buf;
पूर्ण

/* Diagnose 224 functions */

अटल पूर्णांक diag224_get_name_table(व्योम)
अणु
	/* memory must be below 2GB */
	diag224_cpu_names = (अक्षर *) __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!diag224_cpu_names)
		वापस -ENOMEM;
	अगर (diag224(diag224_cpu_names)) अणु
		मुक्त_page((अचिन्हित दीर्घ) diag224_cpu_names);
		वापस -EOPNOTSUPP;
	पूर्ण
	EBCASC(diag224_cpu_names + 16, (*diag224_cpu_names + 1) * 16);
	वापस 0;
पूर्ण

अटल व्योम diag224_delete_name_table(व्योम)
अणु
	मुक्त_page((अचिन्हित दीर्घ) diag224_cpu_names);
पूर्ण

अटल पूर्णांक diag224_idx2name(पूर्णांक index, अक्षर *name)
अणु
	स_नकल(name, diag224_cpu_names + ((index + 1) * DIAG204_CPU_NAME_LEN),
	       DIAG204_CPU_NAME_LEN);
	name[DIAG204_CPU_NAME_LEN] = 0;
	strim(name);
	वापस 0;
पूर्ण

काष्ठा dbfs_d204_hdr अणु
	u64	len;		/* Length of d204 buffer without header */
	u16	version;	/* Version of header */
	u8	sc;		/* Used subcode */
	अक्षर	reserved[53];
पूर्ण __attribute__ ((packed));

काष्ठा dbfs_d204 अणु
	काष्ठा dbfs_d204_hdr	hdr;	/* 64 byte header */
	अक्षर			buf[];	/* d204 buffer */
पूर्ण __attribute__ ((packed));

अटल पूर्णांक dbfs_d204_create(व्योम **data, व्योम **data_मुक्त_ptr, माप_प्रकार *size)
अणु
	काष्ठा dbfs_d204 *d204;
	पूर्णांक rc, buf_size;
	व्योम *base;

	buf_size = PAGE_SIZE * (diag204_buf_pages + 1) + माप(d204->hdr);
	base = vzalloc(buf_size);
	अगर (!base)
		वापस -ENOMEM;
	d204 = page_align_ptr(base + माप(d204->hdr)) - माप(d204->hdr);
	rc = diag204_करो_store(d204->buf, diag204_buf_pages);
	अगर (rc) अणु
		vमुक्त(base);
		वापस rc;
	पूर्ण
	d204->hdr.version = DBFS_D204_HDR_VERSION;
	d204->hdr.len = PAGE_SIZE * diag204_buf_pages;
	d204->hdr.sc = diag204_store_sc;
	*data = d204;
	*data_मुक्त_ptr = base;
	*size = d204->hdr.len + माप(काष्ठा dbfs_d204_hdr);
	वापस 0;
पूर्ण

अटल काष्ठा hypfs_dbfs_file dbfs_file_d204 = अणु
	.name		= "diag_204",
	.data_create	= dbfs_d204_create,
	.data_मुक्त	= vमुक्त,
पूर्ण;

__init पूर्णांक hypfs_diag_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (diag204_probe()) अणु
		pr_err("The hardware system does not support hypfs\n");
		वापस -ENODATA;
	पूर्ण

	अगर (diag204_info_type == DIAG204_INFO_EXT)
		hypfs_dbfs_create_file(&dbfs_file_d204);

	अगर (MACHINE_IS_LPAR) अणु
		rc = diag224_get_name_table();
		अगर (rc) अणु
			pr_err("The hardware system does not provide all "
			       "functions required by hypfs\n");
			debugfs_हटाओ(dbfs_d204_file);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम hypfs_diag_निकास(व्योम)
अणु
	debugfs_हटाओ(dbfs_d204_file);
	diag224_delete_name_table();
	diag204_मुक्त_buffer();
	hypfs_dbfs_हटाओ_file(&dbfs_file_d204);
पूर्ण

/*
 * Functions to create the directory काष्ठाure
 * *******************************************
 */

अटल पूर्णांक hypfs_create_cpu_files(काष्ठा dentry *cpus_dir, व्योम *cpu_info)
अणु
	काष्ठा dentry *cpu_dir;
	अक्षर buffer[TMP_SIZE];
	व्योम *rc;

	snम_लिखो(buffer, TMP_SIZE, "%d", cpu_info__cpu_addr(diag204_info_type,
							    cpu_info));
	cpu_dir = hypfs_सूची_गढ़ो(cpus_dir, buffer);
	rc = hypfs_create_u64(cpu_dir, "mgmtime",
			      cpu_info__acc_समय(diag204_info_type, cpu_info) -
			      cpu_info__lp_समय(diag204_info_type, cpu_info));
	अगर (IS_ERR(rc))
		वापस PTR_ERR(rc);
	rc = hypfs_create_u64(cpu_dir, "cputime",
			      cpu_info__lp_समय(diag204_info_type, cpu_info));
	अगर (IS_ERR(rc))
		वापस PTR_ERR(rc);
	अगर (diag204_info_type == DIAG204_INFO_EXT) अणु
		rc = hypfs_create_u64(cpu_dir, "onlinetime",
				      cpu_info__online_समय(diag204_info_type,
							    cpu_info));
		अगर (IS_ERR(rc))
			वापस PTR_ERR(rc);
	पूर्ण
	diag224_idx2name(cpu_info__ctidx(diag204_info_type, cpu_info), buffer);
	rc = hypfs_create_str(cpu_dir, "type", buffer);
	वापस PTR_ERR_OR_ZERO(rc);
पूर्ण

अटल व्योम *hypfs_create_lpar_files(काष्ठा dentry *प्रणालीs_dir, व्योम *part_hdr)
अणु
	काष्ठा dentry *cpus_dir;
	काष्ठा dentry *lpar_dir;
	अक्षर lpar_name[DIAG204_LPAR_NAME_LEN + 1];
	व्योम *cpu_info;
	पूर्णांक i;

	part_hdr__part_name(diag204_info_type, part_hdr, lpar_name);
	lpar_name[DIAG204_LPAR_NAME_LEN] = 0;
	lpar_dir = hypfs_सूची_गढ़ो(प्रणालीs_dir, lpar_name);
	अगर (IS_ERR(lpar_dir))
		वापस lpar_dir;
	cpus_dir = hypfs_सूची_गढ़ो(lpar_dir, "cpus");
	अगर (IS_ERR(cpus_dir))
		वापस cpus_dir;
	cpu_info = part_hdr + part_hdr__size(diag204_info_type);
	क्रम (i = 0; i < part_hdr__rcpus(diag204_info_type, part_hdr); i++) अणु
		पूर्णांक rc;
		rc = hypfs_create_cpu_files(cpus_dir, cpu_info);
		अगर (rc)
			वापस ERR_PTR(rc);
		cpu_info += cpu_info__size(diag204_info_type);
	पूर्ण
	वापस cpu_info;
पूर्ण

अटल पूर्णांक hypfs_create_phys_cpu_files(काष्ठा dentry *cpus_dir, व्योम *cpu_info)
अणु
	काष्ठा dentry *cpu_dir;
	अक्षर buffer[TMP_SIZE];
	व्योम *rc;

	snम_लिखो(buffer, TMP_SIZE, "%i", phys_cpu__cpu_addr(diag204_info_type,
							    cpu_info));
	cpu_dir = hypfs_सूची_गढ़ो(cpus_dir, buffer);
	अगर (IS_ERR(cpu_dir))
		वापस PTR_ERR(cpu_dir);
	rc = hypfs_create_u64(cpu_dir, "mgmtime",
			      phys_cpu__mgm_समय(diag204_info_type, cpu_info));
	अगर (IS_ERR(rc))
		वापस PTR_ERR(rc);
	diag224_idx2name(phys_cpu__ctidx(diag204_info_type, cpu_info), buffer);
	rc = hypfs_create_str(cpu_dir, "type", buffer);
	वापस PTR_ERR_OR_ZERO(rc);
पूर्ण

अटल व्योम *hypfs_create_phys_files(काष्ठा dentry *parent_dir, व्योम *phys_hdr)
अणु
	पूर्णांक i;
	व्योम *cpu_info;
	काष्ठा dentry *cpus_dir;

	cpus_dir = hypfs_सूची_गढ़ो(parent_dir, "cpus");
	अगर (IS_ERR(cpus_dir))
		वापस cpus_dir;
	cpu_info = phys_hdr + phys_hdr__size(diag204_info_type);
	क्रम (i = 0; i < phys_hdr__cpus(diag204_info_type, phys_hdr); i++) अणु
		पूर्णांक rc;
		rc = hypfs_create_phys_cpu_files(cpus_dir, cpu_info);
		अगर (rc)
			वापस ERR_PTR(rc);
		cpu_info += phys_cpu__size(diag204_info_type);
	पूर्ण
	वापस cpu_info;
पूर्ण

पूर्णांक hypfs_diag_create_files(काष्ठा dentry *root)
अणु
	काष्ठा dentry *प्रणालीs_dir, *hyp_dir;
	व्योम *समय_hdr, *part_hdr;
	पूर्णांक i, rc;
	व्योम *buffer, *ptr;

	buffer = diag204_store();
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	प्रणालीs_dir = hypfs_सूची_गढ़ो(root, "systems");
	अगर (IS_ERR(प्रणालीs_dir)) अणु
		rc = PTR_ERR(प्रणालीs_dir);
		जाओ err_out;
	पूर्ण
	समय_hdr = (काष्ठा x_info_blk_hdr *)buffer;
	part_hdr = समय_hdr + info_blk_hdr__size(diag204_info_type);
	क्रम (i = 0; i < info_blk_hdr__npar(diag204_info_type, समय_hdr); i++) अणु
		part_hdr = hypfs_create_lpar_files(प्रणालीs_dir, part_hdr);
		अगर (IS_ERR(part_hdr)) अणु
			rc = PTR_ERR(part_hdr);
			जाओ err_out;
		पूर्ण
	पूर्ण
	अगर (info_blk_hdr__flags(diag204_info_type, समय_hdr) &
	    DIAG204_LPAR_PHYS_FLG) अणु
		ptr = hypfs_create_phys_files(root, part_hdr);
		अगर (IS_ERR(ptr)) अणु
			rc = PTR_ERR(ptr);
			जाओ err_out;
		पूर्ण
	पूर्ण
	hyp_dir = hypfs_सूची_गढ़ो(root, "hyp");
	अगर (IS_ERR(hyp_dir)) अणु
		rc = PTR_ERR(hyp_dir);
		जाओ err_out;
	पूर्ण
	ptr = hypfs_create_str(hyp_dir, "type", "LPAR Hypervisor");
	अगर (IS_ERR(ptr)) अणु
		rc = PTR_ERR(ptr);
		जाओ err_out;
	पूर्ण
	rc = 0;

err_out:
	वापस rc;
पूर्ण
